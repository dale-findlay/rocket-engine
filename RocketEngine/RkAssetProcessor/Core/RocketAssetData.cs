using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor.Core
{
    public abstract class RocketAssetData
    {
        public byte[] Data { get; protected set; }
        public abstract void ProcessSourceFile(string sourceFilePath);
    }
}
