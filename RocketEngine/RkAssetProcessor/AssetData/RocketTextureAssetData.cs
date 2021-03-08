using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using RkAssetProcessor.Core;
using TeximpNet;

namespace RkAssetProcessor.AssetData
{
    class RocketTextureAssetData : RocketAssetData
    {
        public override void ProcessSourceFile(string sourceFilePath)
        {
            using (Surface image = Surface.LoadFromFile(sourceFilePath))
            {
                image.FlipVertically();

                if (image.ImageType != ImageType.Bitmap || image.BitsPerPixel != 32)
                    image.ConvertTo(ImageConversion.To32Bits);

                using(MemoryStream stream = new MemoryStream())
                {
                    image.SaveToStream(ImageFormat.TARGA, stream, ImageSaveFlags.TARGA_SaveRLE);

                    byte[] streamBytes = stream.GetBuffer();

                    Data = new byte[streamBytes.Length];
                    Array.Copy(streamBytes, Data, streamBytes.Length);
                }
            }
        }
    }
}
