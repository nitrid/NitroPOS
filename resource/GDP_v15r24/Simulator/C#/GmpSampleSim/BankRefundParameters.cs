using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    public partial class BankRefundParameters : Form
    {
        public int _BKMID {get; set; }
        public bool _Reserve1 { get; set; }
        public bool _LoyaltyPointToRefund { get; set; }
        public bool _RRN { get; set; }
        public bool _TransactionReferenceCode { get; set; }
        public bool _OriginalTransactionType { get; set; }
        public bool _OriginalTransactionAmount { get; set; }
        public bool _OriginalLoyaltyAmount { get; set; }
        public bool _OriginalTransactionDate { get; set; }
        public bool _OriginalInstallmentCount { get; set; }
        public bool _AuthorizationNumber { get; set; }
        public bool _OriginalMerchantId { get; set; }
        public bool _CurrencyCodeOfAmountToRefund { get; set; }
        public bool _terminalId { get; set; } 

        public BankRefundParameters(ushort bankBkmId)
        {
            InitializeComponent();
            BankRefundParameters_Init(bankBkmId);
        }
        public BankRefundParameters()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.DialogResult = System.Windows.Forms.DialogResult.OK;
        }

        public void BankRefundParameters_Init(ushort bankBkmId)
        {

            RefundParams[] refpar = new RefundParams[256];

                                            //  BKMID    || AmountToBeRefunded || LoyaltyPointToBeRefunded || RRN   || TransactionReferenceCode || OriginalTransactionType || OriginalTransactionAmount || OriginalLoyaltyAmount || OriginalTransactionDate || OriginalInstallmentCount || AuthorizationNumber || OriginalMerchantId || CurrencyCodeOfAmountToBeRefunded || TerminalId
            refpar[46] =    new RefundParams(46 /*AKBANK */,        true,               false,                true,             true,                   true,                       true,                       true,                       true,                       true,                       true,                   false,                  true,                        true);
            refpar[62] =    new RefundParams(62 /*GARANTI*/,        true,               false,                false,            true,                   true,                       true,                       true,                       true,                       true,                       false,                  true,                   true,                        true);
            refpar[64] =    new RefundParams(64 /*ISBANK */,        true,               false,                true,             false,                  true,                       true,                       true,                       true,                       false,                      true,                   true,                   true,                        true);
            refpar[67] =    new RefundParams(67 /*YKB    */,        true,               false,                true,             true,                   false,                      true,                       true,                       false,                      true,                       true,                   true,                   true,                        true);
            refpar[123] =   new RefundParams(123 /*HSBC   */,       true,               false,                false,            true,                   true,                       false,                      true,                       true,                       false,                      true,                   true,                   false,                       true);
            refpar[253] = new RefundParams(253 /*Default*/,         true,               true,                 true,             true,                   true,                       true,                       true,                       true,                       true,                       true,                   true,                   true,                        true);

            int bankId = 0;

            switch (Convert.ToInt32(bankBkmId))
            {
                case 46:
                    groupBox13.Text = "AKBANK";
                    bankId = 46;
                    break;
                case 62:
                    groupBox13.Text = "GARANTİ";
                    bankId = 62;
                    break;
                case 64:
                    groupBox13.Text = "ISBANK";
                    bankId = 64;
                    break;
                case 67:
                    groupBox13.Text = "YKB";
                    bankId = 67;
                    break;
                case 123:
                    groupBox13.Text = "HSBC";
                    bankId = 123;
                    break;
                case 253:
                    groupBox13.Text = "Tanımsız";
                    bankId = 253;
                    break;
                default:
                    break;
            }

            if (bankId != 0)
            {
                //if (refpar[bankId].Reserve1 == true)
                //    chc_refundPar_00.Checked = true;
                if (refpar[bankId].LoyaltyPointToRefund == true)
                    chc_refundPar_01.Checked = true;
                if (refpar[bankId].RRN == true)
                    chc_refundPar_02.Checked = true;
                if (refpar[bankId].TransactionReferenceCode == true)
                    chc_refundPar_03.Checked = true;
                if (refpar[bankId].OriginalTransactionType == true)
                    chc_refundPar_04.Checked = true;
                if (refpar[bankId].OriginalTransactionAmount == true)
                    chc_refundPar_05.Checked = true;
                if (refpar[bankId].OriginalLoyaltyAmount == true)
                    chc_refundPar_06.Checked = true;
                if (refpar[bankId].OriginalTransactionDate == true)
                    chc_refundPar_07.Checked = true;
                if (refpar[bankId].OriginalInstallmentCount == true)
                    chc_refundPar_08.Checked = true;
                if (refpar[bankId].AuthorizationNumber == true)
                    chc_refundPar_09.Checked = true;
                if (refpar[bankId].OriginalMerchantId == true)
                    chc_refundPar_10.Checked = true;
                if (refpar[bankId].CurrencyCodeOfAmountToRefund == true)
                    chc_refundPar_11.Checked = true;
                if (refpar[bankId].TerminalId == true)
                    chc_refundPar_12.Checked = true;
            }
        }

        private void chc_refundPar_00_CheckedChanged(object sender, EventArgs e)
        {

            CheckBox chc = (CheckBox)sender;

            switch (Convert.ToInt32(chc.Name.Substring(chc.Name.Length-2, 2)))
            {
                //case 0:
                //    _Reserve1 = chc.Checked;
                //    break;
                case 1:
                    _LoyaltyPointToRefund = chc.Checked;
                    break;
                case 2:
                    _RRN = chc.Checked;
                    break;
                case 3:
                    _TransactionReferenceCode = chc.Checked;
                    break;
                case 4:
                    _OriginalTransactionType = chc.Checked;
                    break;
                case 5:
                    _OriginalTransactionAmount = chc.Checked;
                    break;
                case 6:
                    _OriginalLoyaltyAmount = chc.Checked;
                    break;
                case 7:
                    _OriginalTransactionDate = chc.Checked;
                    break;
                case 8:
                    _OriginalInstallmentCount = chc.Checked;
                    break;
                case 9:
                    _AuthorizationNumber = chc.Checked;
                    break;
                case 10:
                    _OriginalMerchantId = chc.Checked;
                    break;
                case 11:
                    _CurrencyCodeOfAmountToRefund = chc.Checked;
                    break;
                case 12:
                    _terminalId = chc.Checked;
                    break;

                default:
                    break;
            }

        }

        private void chc_refundPar_12_CheckedChanged(object sender, EventArgs e)
        {

        }
    }

    public class RefundParams
    {
        public int BKMID;
        public bool Reserve1;
        public bool LoyaltyPointToRefund;
        public bool RRN;
        public bool TransactionReferenceCode;
        public bool OriginalTransactionType;
        public bool OriginalTransactionAmount;
        public bool OriginalLoyaltyAmount;
        public bool OriginalTransactionDate;
        public bool OriginalInstallmentCount;
        public bool AuthorizationNumber;
        public bool OriginalMerchantId;
        public bool CurrencyCodeOfAmountToRefund;
        public bool TerminalId;

        public RefundParams(int m_BKMID, bool m_Reserve1, bool m_LoyaltyPointToRefund, bool m_RRN, bool m_TransactionReferenceCode, bool m_OriginalTransactionType, bool m_OriginalTransactionAmount, bool m_OriginalLoyaltyAmount, bool m_OriginalTransactionDate, bool m_OriginalInstallmentCount, bool m_AuthorizationNumber, bool m_OriginalMerchantId, bool m_CurrencyCodeOfAmountToRefund, bool m_TerminalId)
        {
            BKMID = m_BKMID;
            Reserve1 = m_Reserve1;
            LoyaltyPointToRefund = m_LoyaltyPointToRefund;
            RRN = m_RRN;
            TransactionReferenceCode = m_TransactionReferenceCode;
            OriginalTransactionType = m_OriginalTransactionType;
            OriginalTransactionAmount = m_OriginalTransactionAmount;
            OriginalLoyaltyAmount = m_OriginalLoyaltyAmount;
            OriginalTransactionDate = m_OriginalTransactionDate;
            OriginalInstallmentCount = m_OriginalInstallmentCount;
            AuthorizationNumber = m_AuthorizationNumber;
            OriginalMerchantId = m_OriginalMerchantId;
            CurrencyCodeOfAmountToRefund = m_CurrencyCodeOfAmountToRefund;
            TerminalId = m_TerminalId;
        }
    }
}
