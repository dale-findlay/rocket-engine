using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor.Core
{
    public class SourceFileInfo
    {
        public string originalFilePath;

        public byte[] OriginalFilePathBytes
        {
            get
            {
                return Encoding.UTF8.GetBytes(originalFilePath.ToCharArray());
            }
        }

    }
}
