using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace GmpSampleSim
{
    class ParserClass
    {
        public const string ECR_SERVICE_MODE = "0";
        public const string ECR_USER_MODE = "1";
        public const string ECR_BLOCKED_MODE = "8";
        public const string ECR_MAINTENANCE_MODE = "9";
        public const string ECR_DEMO_MODE = "10";            //0a şeklinde gelme ihtimali var

        public static GMPForm MainControls;

        public byte[] GMP_AscToBcd(string Value)
        {
            byte[] tempbuf = new byte[32];
            byte[] tempbufbcd = new byte[16];
            Encoding asen = Encoding.Default;

            ushort fieldlen = (ushort)Value.Length;
            tempbuf = asen.GetBytes(Value);
            Utility.GMP_AscToBcd(ref tempbufbcd, (ushort)(fieldlen / 2), ref tempbuf, (ushort)fieldlen);

            return tempbufbcd;
        }

        public static void DisplayEcrStatus(ST_GMP_PAIR_RESP stPairResp, ST_ECHO echoStr)
        {

            MainControls.m_tvEcho.Nodes.Clear();

            DisplayStructInTree("dll Version", GMP_Tools.SetEncoding(MainControls.m_dllVersion));

            DisplayStructInTree("Ret Code", echoStr.retcode.ToString("X8"));
            DisplayStructInTree("MTU Size", echoStr.mtuSize.ToString("X4"));
            DisplayStructInTree("Status", echoStr.status.ToString("X8"));
            DisplayStructInTree("KCV", GetValOfStructMember(echoStr.kvc, 8));
            DisplayStructInTree("ECR Brand", stPairResp.szEcrBrand);
            DisplayStructInTree("ECR Model", stPairResp.szEcrModel);
            DisplayStructInTree("ECR Serial Num", stPairResp.szEcrSerialNumber);
            DisplayStructInTree("ECR Version Num", stPairResp.szVersionNumber);
            DisplayStructInTree("Date", echoStr.date.day.ToString().PadLeft(2, '0') + "/" + echoStr.date.month.ToString().PadLeft(2, '0') + "/" + echoStr.date.year.ToString().PadLeft(2, '0'));
            DisplayStructInTree("Time", echoStr.time.hour.ToString().PadLeft(2, '0') + ":" + echoStr.time.minute.ToString().PadLeft(2, '0') + ":" + echoStr.time.second.ToString().PadLeft(2, '0'));
            DisplayStructInTree("ECR Version", GMP_Tools.SetEncoding(echoStr.ecrVersion));
            DisplayStructInTree("Cashier Index", echoStr.activeCashier.index.ToString("X4"));
            DisplayStructInTree("Cashier Name", echoStr.activeCashier.name);
            DisplayStructInTree("Cashier Flags", echoStr.activeCashier.flags.ToString("X8"));
            switch (echoStr.ecrMode.ToString())
            {
                case ECR_SERVICE_MODE:
                    DisplayStructInTree("mode", "ECR_SERVICE_MODE _ 0");
                    break;
                case ECR_USER_MODE:
                    DisplayStructInTree("mode", "ECR_USER_MODE _ 1");
                    break;
                case ECR_BLOCKED_MODE:
                    DisplayStructInTree("mode", "ECR_BLOCKED_MODE _ 8");
                    break;
                case ECR_MAINTENANCE_MODE:
                    DisplayStructInTree("mode", "ECR_MAINTENANCE_MODE _ 9");
                    break;
                case ECR_DEMO_MODE:
                    DisplayStructInTree("mode", "ECR_DEMO_MODE _ 10");
                    break;
                default:
                    DisplayStructInTree("mode", "ECR_INVALID_MODE");
                    break;
            }

            ParseStatusInfo(echoStr.status);

        }

        public static string GetValOfStructMember(byte[] member, int len)
        {
            string str = "";

            for (int i = 0; i < len; i++)
            {
                str += member[i].ToString("X2");
            }
            return str;
        }

        public static string GetValOfStructMemberAscii(byte[] member, int len)
        {
            string str = "";
            byte[] new_arr = new byte[len];

            int j = 0;
            for (int i = 0; i < len; i++)
            {
                if (member[i] != 0x00)
                {
                    new_arr[j] = member[i];
                    j++;
                }
            }
            str += GMP_Tools.SetEncoding(new_arr);

            //for (int i = 0; i < len; i++)
            //{
            //    str += member[i].ToString("X2");
            //}
            return str;
        }

        public static void ParseStatusInfo(uint statusInfo)
        {

            string binValuem = Convert.ToString(statusInfo, 2);

            string[] arrm = new string[] { "GMP3_STATE_BIT_PAIRED", "GMP3_STATE_BIT_KEY_EXPIRED", "GMP3_STATE_BIT_FISCALIZED", "GMP3_STATE_BIT_OKC_MALI_MOD", "GMP3_STATE_BIT_PARAMETRE", "GMP3_STATE_BIT_NO_PAPER" };

            int bitNum = 50;
            for (int j = 0; j < binValuem.Length; j++)
            {
                bitNum = Convert.ToInt32(binValuem.Substring(binValuem.Length - 1 - j, 1));

                switch (bitNum)
                {
                    case 0:
                        break;
                    case 1:
                        DisplayStructInTree(" set bit : " + j.ToString(), "  " + arrm[j]);
                        break;
                    default:
                        break;
                }
            }
        }

        public static void DisplayStructInTree(string memberName, string value)
        {
            MainControls.m_tvEcho.Nodes.Add(memberName.PadRight(20, ' ') + " " + value.PadRight(10, ' '));
        }
    }
}
