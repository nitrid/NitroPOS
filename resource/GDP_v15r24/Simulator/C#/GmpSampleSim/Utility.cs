using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.IO;
using System;
using System.Security.Cryptography;
using System.Collections;
using GmpSampleSim;


/// <summary>
/// Summary description for Class1
/// </summary>
/// 


public class AddValue
{
    private string m_Display;
    private decimal m_Value;
    public AddValue(string Display, decimal Value)
    {
        m_Display = Display;
        m_Value = Value;
    }
    public string Display
    {
        get { return m_Display; }
    }
    public decimal Value
    {
        get { return m_Value; }
    }
}


public class gmpTag
{
    public gmpTag(int pTag, int pType,int pPart,string pDesc)
    {
        this.Tag = pTag;
        this.Type= pType;
        this.Part = pPart;
        this.Desc = pDesc;
    }

    public int  Tag;
    public int  Type;
    public int  Part;
    public string Desc;

}

public class gmpTagList : IEnumerable
{
    private gmpTag[] _gmpTagList;
    public gmpTagList(gmpTag[] pArray)
    {
        _gmpTagList = new gmpTag[pArray.Length];

        for (int i = 0; i < pArray.Length; i++)
        {
            _gmpTagList[i] = pArray[i];
        }
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return (IEnumerator)GetEnumerator();
    }

    public gmpTagListEnum GetEnumerator()
    {
        return new gmpTagListEnum(_gmpTagList);
    }
}

public class gmpTagListEnum : IEnumerator
{
    public gmpTag[] _gmpTagList;

    // Enumerators are positioned before the first element
    // until the first MoveNext() call.
    int position = -1;

    public gmpTagListEnum(gmpTag[] list)
    {
        _gmpTagList = list;
    }

    public bool MoveNext()
    {
        position++;
        return (position < _gmpTagList.Length);
    }

    public void Reset()
    {
        position = -1;
    }

    object IEnumerator.Current
    {
        get
        {
            return Current;
        }
    }

    public gmpTag Current
    {
        get
        {
            try
            {
                return _gmpTagList[position];
            }
            catch (IndexOutOfRangeException)
            {
                throw new InvalidOperationException();
            }
        }
    }
}

public class Utility
{
    public Utility()
	{
		//
		// TODO: Add constructor logic here
		//
	}

    public const int ASCII = 1;
    public const int BCD = 2;
    public const int BINARY = 3;
    public const int APP_TAG = 4;
    public const int MNG_TAG = 5;
    public const int PROTOCOL_TAG = 6;

    public const int STX= 2;
    public const int ETX = 3;


    public static byte[] GMP_AscToBcd(string Value)
    {
        byte[] outBuf = new byte[Value.Length / 2];
        try
        {
            byte[] tempbuf = new byte[32];
            byte[] tempbufbcd = new byte[16];
            Encoding asen = Encoding.Default;

            ushort fieldlen = (ushort)Value.Length;
            tempbuf = asen.GetBytes(Value);
            Utility.GMP_AscToBcd(ref tempbufbcd, (ushort)(fieldlen / 2), ref tempbuf, (ushort)fieldlen);

            for (int i = 0; i < outBuf.Length; i = i + 1)
                outBuf[i] = tempbufbcd[i];

            return outBuf;
        }
        catch (Exception )
        {
            return null;
        }
    }


    static byte[] GetBytes(string str)
    {
            byte[] bytes = new byte[str.Length * sizeof(char)];
            System.Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
            return bytes;
    }
  
    #region PlaFunctions

    #region Pla_AscToU16
    /// <summary>
    /// Converts u16len bytes of Ascii chain to Uint16
    /// </summary>
    /// <param name="pu8StrIn"></param>
    /// <param name="u16Len"></param>
    /// <returns>Uint16</returns>
    public static UInt16 Pla_AscToU16(byte[] pu8StrIn, UInt16 u16Len)
    {
        UInt16 u16Index;
        UInt16 u16Jndex;
        UInt16 u16RetValue;

        u16RetValue = 0;
        for (u16Index = 0, u16Jndex = 1; u16Index < u16Len; ++u16Index, u16Jndex *= 10)
        {
            u16RetValue += System.Convert.ToUInt16((pu8StrIn[u16Len - 1 - u16Index] - 0x30) * u16Jndex);
        }//fin for.

        return (u16RetValue);
    }

    #endregion

    #region Pla_AscToU32
    /// <summary>
    /// Converts u16len bytes of Ascii chain to Uint32
    /// </summary>
    /// <param name="pu8StrIn"></param>
    /// <param name="u16Len"></param>
    /// <returns>UInt32</returns>
    public static UInt32 Pla_AscToU32(byte[] pu8StrIn, UInt16 u16Len)
    {
        UInt16 u16Index;
        UInt32 u32Jndex;
        UInt32 u32RetValue;

        u32RetValue = 0;
        for (u16Index = 0, u32Jndex = 1; u16Index < u16Len; ++u16Index, u32Jndex *= 10)
        {
            u32RetValue += (UInt32)((pu8StrIn[u16Len - 1 - u16Index] - 0x30) * u32Jndex);
        }//fin for.

        return (u32RetValue);
    }

    #endregion

    #region Pla_AscToU64
    /// <summary>
    /// Converts u16len bytes of Ascii chain to Uint64
    /// </summary>
    /// <param name="pu8StrIn"></param>
    /// <param name="u16Len"></param>
    /// <returns>UInt64</returns>
    public static UInt64 Pla_AscToU64(byte[] pu8StrIn, UInt16 u16Len)
    {
        UInt16 u16Index;
        UInt64 u64Jndex;
        UInt64 u64RetValue;

        u64RetValue = 0;
        for (u16Index = 0, u64Jndex = 1; u16Index < u16Len; ++u16Index, u64Jndex *= 10)
        {
            u64RetValue += (UInt64)((ulong)(pu8StrIn[u16Len - 1 - u16Index] - 0x30) * u64Jndex);
        }//fin for.

        return (u64RetValue);
    }// End of Pla_AscToU64

    #endregion

    #region Pla_BcdToAsc
    /// <summary>
    /// Converts a BCD value chain to an ASCII value chain.	
    /// Converts each 'half byte' Qi of the source chain to its ASCII	
    /// value on 1 byte :													
    ///for Qi = 0 to 9 => '0' to '9' (0x30 to 0x39)						
    ///The conversion is processed on u16Len 'half bytes' of the source	
    ///chain to u16Len bytes of the destination chain.						
    ///If u16Len is an odd number, the conversion will start with the		
    ///second 'half byte' of the source chain (the lower 4 bits of the		
    ///first byte).														
    /// </summary>
    /// <param name="pu8PtOut"></param>
    /// <param name="pu8PtIn"></param>
    /// <param name="u16Len"></param>
    /// <returns></returns>

    public static bool Pla_BcdToAsc(ref byte[] pu8PtOut, ref byte[] pu8PtIn, UInt16 u16Len)
    {
        UInt16 u16Index;
        System.Text.Encoding asc = Encoding.Default;

        for (u16Index = 0; u16Index < ((UInt16)((u16Len / 2) + (u16Len % 2))); ++u16Index)
        {
            if (((pu8PtIn[u16Index] & 0x0F) > 0x09) || ((pu8PtIn[u16Index] & 0xF0) > 0x90))
            {
                return false;
            }
        }


        Pla_HexToAsc(ref pu8PtOut, ref pu8PtIn, u16Len);

        return true;
    } // End of Pla_BcdToAsc

    #endregion

    #region Pla_HexToAsc
    /// <summary>
    /// Converts a hexadecimal value chain to an ASCII value chain.	
    ///	Converts each 'half byte' Qi of the source chain to its ASCII		
    ///	value on 1 byte :													
    ///	for Qi = 0 to 9 => '0' to '9' (0x30 to 0x39)						
    ///	for Qi = A to F => 'A' to 'F' (0x41 to 0x46)						
    ///	The conversion is processed on u16Len 'half bytes' of the source	
    ///	chain to u16Len bytes of the destination chain.						
    ///	If u16Len is an odd number, the conversion will start with the		
    ///	second 'half byte' of the source chain (the lower 4 bits of the		
    ///	first byte).														
    ///	Returned: The address of the first byte after the destination chain 
    ///			  (pu8PtOut + u16Len).                                      
    /// </summary>

    public static byte[] Pla_HexToAsc(ref byte[] pu8PtOut, ref byte[] pu8PtIn, UInt16 u16Len)
    {
        UInt16 u16Index = 0, i, tekse;   // Index de travail
        UInt16 pu8Pt;					// Sauvegarde pointeur destination


        //memset(pu8PtOut, 0, u16Len+1);
        // Conversion du champ
        pu8Pt = 0;
        tekse = 0;

        if ((u16Len % 2) == 1)
        {
            pu8PtOut[u16Index] = (byte)((pu8PtIn[u16Index] & 0x0F) + 0x30);
            u16Index++;
            tekse = 1;
        }

        for (i = 0; i < (u16Len / 2); i++)
        {
            pu8PtOut[u16Index++] = (byte)(((pu8PtIn[i + tekse] & 0xF0) >> 4) + 0x30);
            pu8PtOut[u16Index++] = (byte)((pu8PtIn[i + tekse] & 0x0F) + 0x30);
        }//fin for.

        while (pu8Pt != u16Index)
        {
            if (pu8PtOut[pu8Pt] >= 0x3A)
            {
                pu8PtOut[pu8Pt] += (byte)(7);
            }
            pu8Pt++;
        }//fin while.
        pu8Pt = 0;
        return (pu8PtOut);

    } // End of Pla_HexToAsc


    #endregion

    #region Pla_AscToHex
    /// <summary>
    /// 
    /// </summary>
    /// <param name="u8Byte"></param>
    /// <returns></returns>
    public static byte Loc_ByteToNb(byte u8Byte)
    {
        if (u8Byte >= 0x41)
        {
            return Convert.ToByte((u8Byte - 0x07) & 0x0F);
        }//fin if.
        else
        {
            return Convert.ToByte(u8Byte & 0x0F);
        }//fin else.
    }

    public static void Pla_AscToHex(ref byte[] pu8PtOut, UInt16 u16LgOut, ref byte[] pu8PtIn, UInt16 u16LgIn)
    {
        UInt16 u16Index;       /* Index de travail */
        UInt16 inxOut = 0, inxIn = 0;       /* Index de travail */

        /* Conversion du champ */
        inxOut = (UInt16)(inxOut + u16LgOut - ((u16LgIn + 1) / 2));
        if ((u16LgIn % 2) == 1)
        {
            pu8PtOut[inxOut++] = (byte)(Loc_ByteToNb(pu8PtIn[inxIn++]) & 0x0F);
        }//fin if

        for (u16Index = 0; u16Index < (u16LgIn / 2); u16Index++)
        {
            pu8PtOut[inxOut] = (byte)((Loc_ByteToNb(pu8PtIn[inxIn++]) << 4) & 0xF0);
            // LCO 10/01/00: separation en 2 lignes pour le compilateur ARM
            //*pu8PtOut++ =(uint8)( *pu8PtOut + (Loc_ByteToNb(*pu8PtIn++) & 0x0F) ) ;
            pu8PtOut[inxOut] += (byte)(Loc_ByteToNb(pu8PtIn[inxIn++]) & 0x0F);
            inxOut++;
        }//fin for.

        return;
    } // End of Pla_AscToHex
    #endregion

    #region Pla_AscToBcd
    /// <summary>
    /// 
    /// </summary>
    /// <param name="pu8PtOut"></param>
    /// <param name="u16LgOut"></param>
    /// <param name="pu8PtIn"></param>
    /// <param name="u16LgIn"></param>
    /// <returns>True or False</returns>
    public static bool Pla_AscToBcd(ref byte[] pu8PtOut, UInt16 u16LgOut, ref byte[] pu8PtIn, UInt16 u16LgIn)
    {
        UInt16 u16Index;

        for (u16Index = 0; u16Index < u16LgIn; ++u16Index)
        {
            if ((pu8PtIn[u16Index] < '0') || (pu8PtIn[u16Index] > '9'))
            {
                return false;
            }
        }

        Utility.Pla_AscToHex(ref pu8PtOut, u16LgOut, ref pu8PtIn, u16LgIn);
        return true;
    } // End of Pla_AscToBcd
    #endregion

    public static bool  GMP_AscToBcd(ref byte[] pu8PtOut, UInt16 u16LgOut, ref byte[] pu8PtIn, UInt16 u16LgIn)
    {
        UInt16 u16Index;

        for (u16Index = 0; u16Index < u16LgIn; ++u16Index)
        {
            if ((pu8PtIn[u16Index] < '0') || (pu8PtIn[u16Index] > '9'))
            {
                return false;
            }
        }

        Utility.Pla_AscToHex(ref pu8PtOut, u16LgOut, ref pu8PtIn, u16LgIn);
        return true;
    } // End of Pla_AscToBcd


    #region PutStr
    public static void PutStr(ref byte[] buf, int destIndex, byte[] src, int srcIndex, int len)
    {
        int len2;
        len2 = src.Length;
        if (src.Length > len)
            len2 = len;

        for (; srcIndex < len2; srcIndex++, destIndex++)
        {
            buf[destIndex] = src[srcIndex];
        }
        for (; srcIndex < len; srcIndex++, destIndex++)
            buf[destIndex] = 0x20;

    }

    #endregion

    #region PutNbr
    public static void PutNbr(ref byte[] buf, int destIndex, byte[] src, int srcIndex, int len)
    {
        int diff, i;
        diff = len - src.Length;
        for (i = 0; i < diff; i++)
            buf[destIndex++] = 0x30;

        for (i = diff; i < len; i++)
        {
            buf[destIndex++] = src[srcIndex++];
        }

    }

    #endregion

    #region PutNbrBCD
    public static void PutNbrBCD(ref byte[] buf, int destIndex, byte[] src, int srcIndex, int len)
    {
        int diff, i;
        diff = len - src.Length;
        for (i = 0; i < diff; i++)
            buf[destIndex++] = 0x00;

        for (i = diff; i < len; i++)
        {
            buf[destIndex++] = src[srcIndex++];
        }

    }

    #endregion

    #region FillSpace
    public static void FillSpace(ref byte[] array, int len, int index)
    {
        int i;
        for (i = index; i < len; i++)
        {
            array[i] = 0x20;
        }
    }
    #endregion

    #region IsAlpha
    public static bool IsAlpha(string str)
    {
        int i;
        for (i = 0; i < str.Length; i++)
        {
            if ((str[i] >= 'a' && str[i] <= 'f') ||
                (str[i] >= 'A' && str[i] <= 'F'))
                return true;
        }

        return false;
    }
    #endregion

    public static ushort CalculateCRC(byte[] buf,int len)
    {

        ushort Crc = 0xffff;
        int pos = 0;

        while (len>0)
        {
            Crc = (ushort)(CrcTable[((Crc >> 8) ^ buf[pos])] ^ (Crc << 8));
            len--;
            pos++;
        }
        
        //byte[] vOut = BitConverter.GetBytes(Crc);
        return (Crc);
        
    }

     static ushort[] CrcTable = new ushort []
     {
            0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108, 0x9129,
            0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, 0x1231, 0x0210, 0x3273, 0x2252,
            0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C,
            0xF3FF, 0xE3DE, 0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
            0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D, 0x3653, 0x2672,
            0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738,
            0xF7DF, 0xE7FE, 0xD79D, 0xC7BC, 0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861,
            0x2802, 0x3823, 0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
            0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC,
            0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, 0x6CA6, 0x7C87, 0x4CE4, 0x5CC5,
            0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B,
            0x8D68, 0x9D49, 0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
            0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78, 0x9188, 0x81A9,
            0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3,
            0x5004, 0x4025, 0x7046, 0x6067, 0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C,
            0xE37F, 0xF35E, 0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
            0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3,
            0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 0xA7DB, 0xB7FA, 0x8799, 0x97B8,
            0xE75F, 0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676,
            0x4615, 0x5634, 0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
            0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3, 0xCB7D, 0xDB5C,
            0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A, 0x4A75, 0x5A54, 0x6A37, 0x7A16,
            0x0AF1, 0x1AD0, 0x2AB3, 0x3A92, 0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B,
            0x9DE8, 0x8DC9, 0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
            0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36,
            0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
           };

    #endregion
}
