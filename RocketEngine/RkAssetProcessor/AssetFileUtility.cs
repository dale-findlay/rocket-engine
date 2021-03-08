using RkAssetProcessor.Core;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor
{
    static class AssetFileUtility
    {
        static Dictionary<string, RocketAssetType> supportedTypeMap = new Dictionary<string, RocketAssetType>();

        public static void BuildTypeMap()
        {
            supportedTypeMap.Clear();

            supportedTypeMap.Add("png", RocketAssetType.Texture);
            supportedTypeMap.Add("jpeg", RocketAssetType.Texture);
            supportedTypeMap.Add("jpg", RocketAssetType.Texture);
            supportedTypeMap.Add("tga", RocketAssetType.Texture);
            supportedTypeMap.Add("fbx", RocketAssetType.Mesh);
            supportedTypeMap.Add("obj", RocketAssetType.Mesh);
            supportedTypeMap.Add("glsl", RocketAssetType.Shader);
            supportedTypeMap.Add("material", RocketAssetType.Material);
        }

        public static string GetFileExtension(string filePath)
        {
            string ext = Path.GetExtension(filePath);
            ext = ext.ToLower();

            return ext;
        }

        public static RocketAssetType DeriveAssetType(string filePath)
        {
            string fileExt = GetFileExtension(filePath);

            fileExt = fileExt.Replace(".", "");

            if (supportedTypeMap.ContainsKey(fileExt))
            {
                return supportedTypeMap[fileExt];
            }

            return RocketAssetType.Unsupported;
        }
    }
}
