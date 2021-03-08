using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RkAssetProcessor.Core;

namespace RkAssetProcessor.AssetData
{
    class RocketMeshAssetData : RocketAssetData
    {
        public override void ProcessSourceFile(string sourceFilePath)
        {
            string fileType = AssetFileUtility.GetFileExtension(sourceFilePath);

            if(fileType == "obj")
            {

            }
        }
    }
}
