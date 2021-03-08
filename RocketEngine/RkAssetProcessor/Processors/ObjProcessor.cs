using Assimp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor.Data
{
    class RocketMesh
    {

    }

    static class AssimpProcessor
    {
        static RocketMesh LoadFromFile(string filePath)
        {
            AssimpContext importer = new AssimpContext();

            Scene scene = importer.ImportFile(filePath);

            return null;
        }
    }
}
