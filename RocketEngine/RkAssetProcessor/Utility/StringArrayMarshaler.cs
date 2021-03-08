using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace RkAssetProcessor.Utility
{
    public class StringArrayMarshaler : ICustomMarshaler
    {
        public static ICustomMarshaler GetInstance(String cookie)
        {
            return new StringArrayMarshaler();
        }

        public Object MarshalNativeToManaged(IntPtr pNativeData)
        {
            //if (IntPtr.Zero == pNativeData) return null;
            //// Start by reading the size of the array ("Length" from your ABS_DATA struct)
            //int length = Marshal.ReadInt32(pNativeData);
            //// Create the managed array that will be returned
            //T[] array = new T[length];
            //// For efficiency, only compute the element size once
            //int elSiz = Marshal.SizeOf<T>();
            //// Populate the array
            //for (int i = 0; i < length; i++)
            //{
            //    array[i] = Marshal.PtrToStructure<T>(pNativeData + sizeof(int) + (elSiz * i));
            //}
            //// Alternate method, for arrays of primitive types only:
            //// Marshal.Copy(pNativeData + sizeof(int), array, 0, length);
            //return array;

            return null;
        }

        public IntPtr MarshalManagedToNative(Object ManagedObject)
        {
            if (null == ManagedObject) return IntPtr.Zero;
            string[] array = (string[])ManagedObject;

            int charCount = 0;
            foreach(string s in array)
            {
                charCount += s.Length + 1; //+1 for null terminator.
            }

            char[] stringAsChars = new char[charCount];
            int destinationIndex = 0;
            foreach (string s in array)
            {
                //Copy our string bytes.
                char[] sArr = s.ToCharArray();
                Array.Copy(sArr, 0, stringAsChars, destinationIndex, sArr.Length);
                destinationIndex += sArr.Length;
                
                //add our null terminator.
                stringAsChars[destinationIndex] = '\0'; //null terminator;
                destinationIndex++; //for our null terminator
            }

            int size = charCount * sizeof(char);
            IntPtr ptr = Marshal.AllocHGlobal(size);
            Marshal.Copy(stringAsChars, 0, ptr, size);
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
            return -1;
        }
    }
}
