using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor.Utility
{
    public class ArrayMarshaler<T> : ICustomMarshaler
    {
        public static ICustomMarshaler GetInstance(String cookie)
        {
            return new ArrayMarshaler<T>();
        }

        public Object MarshalNativeToManaged(IntPtr pNativeData)
        {
            return null;
        }

        public IntPtr MarshalManagedToNative(Object ManagedObject)
        {
        
            if (null == ManagedObject) return IntPtr.Zero;
            T[] array = (T[])ManagedObject; 
            int elSiz = Marshal.SizeOf<T>();
            int size = elSiz * array.Length;
            IntPtr ptr = Marshal.AllocHGlobal(size);            
            for (int i = 0; i < array.Length; i++)
            {
                Marshal.StructureToPtr<T>(array[i], ptr + (elSiz * i), false);
            }
            return ptr;
        }

        public void CleanUpNativeData(IntPtr pNativeData)
        {
            Marshal.FreeHGlobal(pNativeData);
        }

        public void CleanUpManagedData(Object ManagedObj)
        { }

        public int GetNativeDataSize()
        {
            return sizeof(int) + Marshal.SizeOf<T>();
        }
    }
}
