using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace GmpSampleSim
{
    class LocalizationClass
    {
        public static GMPForm gmpUI;

        public void SetDefault()
        {
            gmpUI.m_cmbInvoiceType.Items.Clear();
            gmpUI.m_cmbMovieType.Items.Clear();
            gmpUI.m_cmbTicketType.Items.Clear();

            gmpUI.groupBox3.Text = Localization.groupBox3;
            gmpUI.groupBox4.Text = Localization.groupBox4;
            gmpUI.groupBox5.Text = Localization.groupBox5;
            gmpUI.groupBox6.Text = Localization.groupBox6;
            gmpUI.handleToolStripMenuItem.Text = Localization.handleToolStripMenuItem;
            gmpUI.label10.Text = Localization.label10;
            gmpUI.label11.Text = Localization.label11;
            gmpUI.label12.Text = Localization.label12;
            gmpUI.label13.Text = Localization.label13;
            gmpUI.label2.Text = Localization.label2;
            gmpUI.label100.Text = Localization.label100;
            gmpUI.label3.Text = Localization.label3;
            gmpUI.label4.Text = Localization.label4;
            gmpUI.label5.Text = Localization.label5;
            gmpUI.label6.Text = Localization.label6;
            gmpUI.label7.Text = Localization.label7;
            gmpUI.label8.Text = Localization.label8;
            gmpUI.label9.Text = Localization.label9;
            gmpUI.m_btn_031.Text = Localization.m_btn_031;
            gmpUI.m_btn_032.Text = Localization.m_btn_032;
            gmpUI.m_getUniqueIDMenuItem.Text = Localization.m_btn_033;
            gmpUI.m_readCardMenuItem.Text = Localization.m_btn_034;
            gmpUI.m_cashPaymentMenuItem.Text = Localization.m_btn_035;
            gmpUI.m_cashAdvantageMenuItem.Text = Localization.m_btn_036;
            gmpUI.m_TaxAndDeptMenuItem.Text = Localization.m_btn_039;
            gmpUI.m_cashierTableMenuItem.Text = Localization.m_btn_040;
            gmpUI.m_transactionsMenuItem.Text = Localization.m_btn_041;
            gmpUI.m_btnPaymentCash.Text = Localization.m_btn_042;
            gmpUI.m_btn_043.Text = Localization.m_btn_043;
            gmpUI.m_currencyTableMenuItem.Text = Localization.m_btn_044;
            gmpUI.m_btn_046.Text = Localization.m_btn_046;
            gmpUI.m_btn_047.Text = Localization.m_btn_047;
            gmpUI.m_btn_048.Text = Localization.m_btn_048;
            gmpUI.m_btn_049.Text = Localization.m_btn_049;
            gmpUI.m_setUniqueIDMenuItem.Text = Localization.m_btn_050;
            gmpUI.m_btn_051.Text = Localization.m_btn_051;
            gmpUI.m_btn_052.Text = Localization.m_btn_052;
            gmpUI.m_btn_053.Text = Localization.m_btn_053;
            gmpUI.m_btn_054.Text = Localization.m_btn_054;
            gmpUI.m_btn_055.Text = Localization.m_btn_055;
            gmpUI.m_btn_TicketSale.Text = Localization.m_btn_TicketSale;
            gmpUI.m_btnAddUserMessage.Text = Localization.m_btnAddUserMessage;
            gmpUI.m_btnAllTicket.Text = Localization.m_btnAllTicket;
            gmpUI.m_btnCompleteUserMessage.Text = Localization.m_btnCompleteUserMessage;
            gmpUI.m_btnJustOneItem.Text = Localization.m_btnJustOneItem;
            gmpUI.m_btnReloadTransaction.Text = Localization.m_btnK_029;
            gmpUI.m_functionMessageMenuItem.Text = Localization.m_btnK_030;
            gmpUI.m_userMessageMenuItem.Text = Localization.m_btn_056;
            gmpUI.m_btnSendInvoice.Text = Localization.m_btnSendInvoice;
            gmpUI.m_closeHandleMenuItem.Text = Localization.m_closeHandleMenuItem;
            gmpUI.m_langOptMenuItem.Text = Localization.m_langOptMenuItem;
            gmpUI.m_openHandleMenuItem.Text = Localization.m_openHandleMenuItem;
            gmpUI.m_printBeforeMfMenuItem.Text = Localization.m_printBeforeMfMenuItem;
            gmpUI.m_printMfMenuItem.Text = Localization.m_printMfMenuItem;
            gmpUI.m_printTicketHeaderMenuItem.Text = Localization.m_printTicketHeaderMenuItem;
            gmpUI.m_printTotalMenuItem.Text = Localization.m_printTotalMenuItem;
            gmpUI.m_settingsMenuItem.Text = Localization.m_settingsMenuItem;
            gmpUI.m_btnStartPairing.Text = Localization.m_startPairingMenuItem;
            gmpUI.radioButton11.Text = Localization.radioButton11;
            gmpUI.radioButton12.Text = Localization.radioButton12;
            gmpUI.radioButton13.Text = Localization.radioButton13;
            gmpUI.tabPage1.Text = Localization.tabPage1;
            gmpUI.groupBox15.Text = Localization.tabPage3;
            gmpUI.groupBox11.Text = Localization.tabPage5;
            gmpUI.groupBox12.Text = Localization.tabPage6;
            gmpUI.tabPage8.Text = Localization.tabPage8;
            gmpUI.tabPage9.Text = Localization.tabPage9;

            gmpUI.m_cmbInvoiceType.Items.Add(Localization.m_cmbInvoiceType_1);
            gmpUI.m_cmbInvoiceType.Items.Add(Localization.m_cmbInvoiceType_2);
            gmpUI.m_cmbInvoiceType.Items.Add(Localization.m_cmbInvoiceType_3);
            gmpUI.m_cmbMovieType.Items.Add(Localization.m_cmbMovieType_1);
            gmpUI.m_cmbMovieType.Items.Add(Localization.m_cmbMovieType_2);
            gmpUI.m_cmbTicketType.Items.Add(Localization.m_cmbTicketType_1);
            gmpUI.m_cmbTicketType.Items.Add(Localization.m_cmbTicketType_2);
            gmpUI.m_cmbTicketType.Items.Add(Localization.m_cmbTicketType_3);
            gmpUI.m_cmbTicketType.Items.Add(Localization.m_cmbTicketType_4);


            gmpUI.checkBox1.Text = Localization.checkBox1;
            gmpUI.groupBox8.Text = Localization.groupBox8;
            gmpUI.label15.Text = Localization.label15;
            gmpUI.label16.Text = Localization.label16;
            gmpUI.label17.Text = Localization.label17;
            gmpUI.label18.Text = Localization.label18;
            gmpUI.label19.Text = Localization.label19;
            gmpUI.m_btnSendFunctionMessage.Text = Localization.m_btnSendFunctionMessage;
            gmpUI.radioButton01.Text = Localization.radioButton01;
            gmpUI.radioButton02.Text = Localization.radioButton02;
            gmpUI.radioButton03.Text = Localization.radioButton03;
            gmpUI.radioButton04.Text = Localization.radioButton04;
            gmpUI.radioButton025.Text = Localization.radioButton05;
            gmpUI.radioButton06.Text = Localization.radioButton06;
            gmpUI.radioButton07.Text = Localization.radioButton07;
            gmpUI.radioButton_12.Text = Localization.radioButton14;
            gmpUI.radioButton15.Text = Localization.radioButton15;
            gmpUI.radioButton16.Text = Localization.radioButton16;

            gmpUI.m_btnVoidAllTicket_059.Text = Localization.m_btnVoidAllTicket;
            gmpUI.m_functionsMenuItem.Text = Localization.m_functionsMenuItem;
            gmpUI.m_pluReadMenuItem.Text = Localization.m_pluReadMenuItem;
            gmpUI.m_SalePluToolStripMenuItem.Text = Localization.m_SalePluToolStripMenuItem;

            gmpUI.userDataToolStripMenuItem.Text = Localization.m_functionsMenuItem;
            gmpUI.m_ParkingEntryMenuItem.Text = Localization.m_ParkingEntryMenuItem;
            //gmpUI.m_TaxFreeRefundMenuItem.Text = Localization.m_TaxFreeRefundMenuItem;
            gmpUI.m_getSetTicketHeaderMenuItem.Text = Localization.m_getSetTicketHeaderMenuItem;
            gmpUI.m_jumpToECRSinglePaymentMenuItem.Text = Localization.m_jumpToECRSinglePaymentMenuItem;
            gmpUI.m_pluDataBaseMenuItem.Text = Localization.m_pluDataBaseMenuItem;
            gmpUI.m_CustomerAdvantageMenuItem.Text = Localization.m_CustomerAdvantageMenuItem;
            gmpUI.m_taxFreeTicketMenuItem.Text = Localization.m_taxFreeTicketMenuItem;
            gmpUI.m_btnCashPaymentMenuItem.Text = Localization.m_btnCashPaymentMenuItem;
            gmpUI.m_btnReversePayment_033.Text = Localization.m_btnReversePayment_033;
            gmpUI.m_btnOtherPayment_034.Text = Localization.m_btnOtherPayment_034;
            gmpUI.m_rbSingleMode.Text = Localization.m_rbSingleMode;
            gmpUI.m_rbBatchMode.Text = Localization.m_rbBatchMode;
            gmpUI.groupBox1.Text = Localization.groupBox1;
            gmpUI.label22.Text = Localization.label22;
            gmpUI.label25.Text = Localization.label25;
            gmpUI.label24.Text = Localization.label24;
            gmpUI.label23.Text = Localization.label23;
            gmpUI.m_btnServiceComplete.Text = Localization.Complete;
            gmpUI.m_btnCompleteJumpToEcr.Text = Localization.Complete;
            gmpUI.m_btnCompleteReversePayment.Text = Localization.Complete;
            gmpUI.m_btnCompleteOtherPayment.Text = Localization.Complete;
            gmpUI.m_btnSendFunctionMessage.Text = Localization.Complete;
            gmpUI.m_btnCompleteUserMessage.Text = Localization.Complete;
            gmpUI.m_btnCompleteMatrahsiz.Text = Localization.Complete;
            gmpUI.tabPage5.Text = Localization.tabPage5_General;
            gmpUI.tabPage10.Text = Localization.tabPage10;
            gmpUI.tabPage3.Text = Localization.tabPage3_Payment;
            gmpUI.tabPage6.Text = Localization.tabPage6_Batch;
            gmpUI.tabPage7.Text = Localization.tabPage7;
            gmpUI.m_btnClearList.Text = Localization.m_btnClearList;
            gmpUI.m_btnSendOnCable.Text = Localization.m_btnSendOnCable;
            gmpUI.m_btnAddUserMessage.Text = Localization.m_btnAddUserMessage;
            gmpUI.m_btnRemoveBitmapFiles.Text = Localization.m_btnRemoveBitmapFiles;
            gmpUI.m_btnDownloadBitmapFiles.Text = Localization.m_btnDownloadBitmapFiles;
            gmpUI.m_btnGetBitmapFiles.Text = Localization.m_btnGetBitmapFiles;
            gmpUI.m_chcTaxFreeActive.Text = Localization.m_chcTaxFreeActive;
            gmpUI.m_setUniqueIDMenuItem.Text = Localization.m_setUniqueIDMenuItem;
            gmpUI.m_getUniqueIDMenuItem.Text = Localization.m_getUniqueIDMenuItem;
            gmpUI.m_getTSMUniqueIDMenuItem.Text = Localization.m_getTSMUniqueIDMenuItem;
            gmpUI.radioButton022.Text = Localization.radioButton022;
            gmpUI.radioButton028.Text = Localization.radioButton028;
            gmpUI.radioButton017.Text = Localization.radioButton017;
       
            
        }
       
    }
}
