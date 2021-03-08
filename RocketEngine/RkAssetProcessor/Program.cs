using RkAssetProcessor.AssetData;
using RkAssetProcessor.Core;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor
{
    enum RocketProcessorMode
    {
        File,
        Directory
    }

    class RocketProcessorSettings
    {
        public RocketProcessorMode mode { get; set; }
        public string file { get; set; }
        public string directory { get; set; }
        public bool recursiveDirectory { get; set; }
        public string outputDirectory { get; set; }
    }

    class Program
    {
        /* 
           Rocket Processor (rkp)

           Input Flags (Required) (one of below):
               * file - process a single file | -f "file.txt"             
               * directory - process an entire directory | -d "C:\hello world\my files"

           Optional Input Flags:
               * recursive - when -d (directory) is provided, process the directory recursivly (all files and file in subfolders). | -r

           Output Flag (Required):
               * game files directory - the output directory of the game files | -g "C:\p4\myamazinggame\Content"
        */

        static RocketProcessorSettings ParseCommandLine(string[] args)
        {
            RocketProcessorSettings settings = new RocketProcessorSettings();


            for (var i = 0; i < args.Length; ++i)
            {
                string currentArg = args[i];

                //single args
                if (currentArg == "-r")
                {
                    settings.recursiveDirectory = true;
                    continue;
                }

                if (i + 1 < args.Length)
                {
                    //duel args.
                    string nextArg = args[i + 1];

                    if (currentArg == "-f")
                    {
                        settings.mode = RocketProcessorMode.File;
                        settings.file = nextArg;
                        continue;
                    }

                    if (currentArg == "-d")
                    {
                        settings.mode = RocketProcessorMode.Directory;
                        settings.directory = nextArg;
                        continue;
                    }

                    if (currentArg == "-g")
                    {
                        settings.outputDirectory = nextArg;
                        continue;
                    }
                }
            }

            return settings;
        }

        static void Main(string[] args)
        {
            AssetFileUtility.BuildTypeMap();

            RocketProcessorSettings settings = ParseCommandLine(args);

            List<string> workingFileSet = new List<string>();

            if (settings.mode == RocketProcessorMode.File)
            {
                workingFileSet.Add(settings.file);
            }

            foreach (string file in workingFileSet)
            {
                RocketAsset asset = ProcessFile(file, settings);

                if (asset != null)
                {
                    string destination = asset.GenerateGameFilePath(settings.outputDirectory);

                    WriteFileToDisk(asset, destination);
                }
            }
        }

        private static void WriteFileToDisk(RocketAsset asset, string destination)
        {
            Directory.CreateDirectory(Path.GetDirectoryName(destination)); //create the destination directory if needed.
            
            using(StreamWriter streamWriter = new StreamWriter(destination))
            {
                using(BinaryWriter writer = new BinaryWriter(streamWriter.BaseStream, Encoding.Default, true))
                {
                    //RkAssetSpec
                    writer.Write(asset.fileVersion);
                    writer.Write((int)asset.fileType);


                    UInt32 ReferencedAssetPathsBytesLength = (uint)asset.ReferencedAssetPathsBytes.Length;
                    writer.Write(ReferencedAssetPathsBytesLength);
                    writer.Write(asset.ReferencedAssetPathsBytes);

                    UInt32 OriginalFilesBytesLength = (uint)asset.sourceFileInfo.OriginalFilePathBytes.Length;
                    writer.Write(OriginalFilesBytesLength);
                    writer.Write(asset.sourceFileInfo.OriginalFilePathBytes);

                    UInt32 AssetDataBytesLength = (uint)asset.assetData.Data.Length;
                    writer.Write(asset.assetData.Data);
                }
            }
        }

        private static RocketAsset ProcessFile(string file, RocketProcessorSettings settings)
        {
            var rktype = AssetFileUtility.DeriveAssetType(file);

            var rkAsset = new RocketAsset();
            rkAsset.fileType = rktype;
            rkAsset.fileVersion = 1;
            rkAsset.sourceFileInfo = new SourceFileInfo()
            {
                originalFilePath = file
            };

            List<string> referencedAssets = new List<string>();
            
            RocketAssetData data = ConstructData(rktype);
            if (data == null)
            {
                return null;
            }

            data.ProcessSourceFile(file);

            rkAsset.referencedAssetPaths = referencedAssets;
            rkAsset.assetData = data;

            return rkAsset;
        }

        private static RocketAssetData ConstructData(RocketAssetType rktype)
        {
            switch (rktype)
            {
                case RocketAssetType.Mesh:
                    {
                        return new RocketMeshAssetData();
                    }
                case RocketAssetType.Texture:
                    {
                        return new RocketTextureAssetData();
                    }

                case RocketAssetType.Shader:
                    {
                        return new RocketShaderAssetData();
                    }
                case RocketAssetType.Material:
                    {
                        return new RocketMaterialAssetData();
                    }
            }

            return null;
        }
    }
}
