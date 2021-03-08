using RkAssetProcessor.Utility;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor.Core
{
    public class RocketAsset
    {
        /// <summary>
        /// The file spec version.
        /// </summary>
        public int fileVersion;

        /// <summary>
        /// The file type (Mesh, Texture, etc). <seealso cref="RocketAssetType"/>
        /// </summary>
        public RocketAssetType fileType;

        /// <summary>
        /// A list of all referenced asset paths. this is used by the engine to build dependency graphs for asset use.
        /// </summary>
        public List<string> referencedAssetPaths;

        public byte[] ReferencedAssetPathsBytes
        {
            get
            {
                int charCount = 0;
                foreach (string s in referencedAssetPaths)
                {
                    charCount += s.Length + 1; //+1 for null terminator.
                }

                char[] stringAsChars = new char[charCount];
                int destinationIndex = 0;
                foreach (string s in referencedAssetPaths.ToArray())
                {
                    //Copy our string bytes.
                    char[] sArr = s.ToCharArray();
                    Array.Copy(sArr, 0, stringAsChars, destinationIndex, sArr.Length);
                    destinationIndex += sArr.Length;

                    //add our null terminator.
                    stringAsChars[destinationIndex] = '\0'; //null terminator;
                    destinationIndex++; //for our null terminator
                }

                return Encoding.UTF8.GetBytes(stringAsChars);
            }
        }

        /// <summary>
        /// Information about the original source file (used before processing). <seealso cref="SourceFileInfo"/>
        /// </summary>
        public SourceFileInfo sourceFileInfo;

        /// <summary>
        /// The raw data associated with this asset.
        /// </summary>
        public RocketAssetData assetData;

        /// <summary>
        /// Generates a file path based on the source file information and provided game directory.
        /// </summary>
        /// <param name="outputDir"></param>
        /// <returns></returns>
        public string GenerateGameFilePath(string outputDir)
        {
            string fileName = Path.GetFileNameWithoutExtension(sourceFileInfo.originalFilePath);
            fileName += ".rkasset";

            RocketAssetType assetType = AssetFileUtility.DeriveAssetType(sourceFileInfo.originalFilePath);
            string folder = RocketAssetTypeUtility.GetAssetTypeName(assetType);
            
            return Path.Combine(outputDir, folder, fileName);
        }

    }

    //public class RocketAssetBinHelper
    //{
    //    public static RocketAssetBin GenerateBin(RocketAsset asset)
    //    {
    //        RocketAssetBin bin = new RocketAssetBin();
    //        bin.fileVersion = asset.fileVersion;
    //        bin.fileType = (int)asset.fileType;
    //        bin.originalFilePathData = asset.sourceFileInfo.originalFilePath;
    //        bin.referencedAssetPathsBytesLength = (uint)GetStringArrayBytesLength(asset.referencedAssetPaths.ToArray());

    //        char[] stringAsChars = new char[bin.referencedAssetPathsBytesLength];
    //        int destinationIndex = 0;
    //        foreach (string s in asset.referencedAssetPaths.ToArray())
    //        {
    //            //Copy our string bytes.
    //            char[] sArr = s.ToCharArray();
    //            Array.Copy(sArr, 0, stringAsChars, destinationIndex, sArr.Length);
    //            destinationIndex += sArr.Length;

    //            //add our null terminator.
    //            stringAsChars[destinationIndex] = '\0'; //null terminator;
    //            destinationIndex++; //for our null terminator
    //        }
    //        bin.referencedAssetPathsData = Encoding.UTF8.GetBytes(stringAsChars);

    //        bin.dataBytesLength = (uint)asset.assetData.Data.Length * sizeof(byte);
    //        bin.dataBytes = asset.assetData.Data;

    //        return bin;
    //    }

    //    public static int GetStringArrayBytesLength(string[] array)
    //    {
    //        int charCount = 0;
    //        foreach (string s in array)
    //        {
    //            charCount += s.Length + 1; //+ 1 for null terminator.
    //        }

    //        return charCount * sizeof(char);
    //    }

    //    public static int GetStringBytesLength(string s)
    //    {
    //        int charCount = 0;
    //        charCount += s.Length + 1; //+ 1 for null terminator.

    //        return charCount * sizeof(char);
    //    }
    //}

    //[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1), Serializable]
    //public struct RocketAssetBin
    //{
    //    /**
    //     * File details
    //     */
    //    public int fileVersion;
    //    public int fileType;

    //    /**
    //     * Referenced Asset Paths.
    //     */
    //    public UInt32 referencedAssetPathsBytesLength;
        
    //    [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)]
    //    public IntPtr referencedAssetPathsData;

    //    /**
    //     * Source file Info.
    //     */
    //    [MarshalAs(UnmanagedType.LPWStr)] //using this marshal type includes the null terminator!
    //    public string originalFilePathData;

    //    /**
    //     * Asset Data
    //     */
    //    public UInt32 dataBytesLength;        
    //    [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 5)]
    //    public IntPtr dataBytes;

    //    public int GetSize()
    //    {
    //        int size = 0;
    //        size += Marshal.SizeOf<int>(); //fileVersion
    //        size += Marshal.SizeOf<int>(); //fileType
            
    //        size += Marshal.SizeOf<UInt32>(); //referencedAssetPathsBytesLength
    //        size += (int)referencedAssetPathsBytesLength;

    //        size += RocketAssetBinHelper.GetStringBytesLength(originalFilePathData);

    //        size += Marshal.SizeOf<UInt32>(); //dataBytesLength
    //        size += (int)dataBytesLength; //dataBytes

    //        return size;
    //    }
    //}
}
