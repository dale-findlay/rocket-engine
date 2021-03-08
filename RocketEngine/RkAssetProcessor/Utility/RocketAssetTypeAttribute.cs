using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor.Utility
{
    [System.AttributeUsage(AttributeTargets.All, Inherited = false, AllowMultiple = false)]
    sealed class RocketAssetTypeAttribute : Attribute
    {
        public RocketAssetTypeAttribute()
        {}

        public string FolderName { get; set; }
    }
}
