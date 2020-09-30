package com.swrd.gmp;

import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JLabel;

import java.awt.Font;

import javax.swing.JTextField;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import javax.swing.border.TitledBorder;

import java.awt.SystemColor;
import java.time.ZonedDateTime;
import java.util.Properties;

import javax.swing.JCheckBox;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import org.jdatepicker.impl.DateComponentFormatter;
import org.jdatepicker.impl.JDatePanelImpl;
import org.jdatepicker.impl.JDatePickerImpl;
import org.jdatepicker.impl.UtilDateModel;

import com.swrd.gmp.GmpDll.ST_FunctionParameters;

public class Functions extends JDialog {
	private JTextField edtZ1;
	private JTextField edtZ2;
	private JTextField edtFis1;
	private JTextField edtFis2;
	private JTextField edtEkuNo;
	private JPanel pnlDateData;
	private final JButton btnOk = new JButton("Ok");
	final String PASS = "2049";
	
	GmpDriver gmpDriver;
	JLabel lblFonksiyonlar;
	UtilDateModel model;
	UtilDateModel model2;
	final JCheckBox chckbxIsDate;
	/**
	 * Launch the application.
	 
	public static void main(String[] args) {
		try {
			Fonksiyonlar dialog = new Fonksiyonlar();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}*/
	public int start() {
		
		ErrorClass.lblError = lblFonksiyonlar;
		
		try {
			this.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			this.setModal(true);
			this.setVisible(true); 
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return 1;
		
	}
	/**
	 * Create the dialog.
	 */
	public Functions(GmpDriver gmpDriverObj) {
		
		gmpDriver = gmpDriverObj;
		
		setBounds(100, 100, 501, 450);
		getContentPane().setLayout(null);
		
		final JRadioButton rdbtnZRaporu = new JRadioButton("Z Raporu");
		rdbtnZRaporu.setBounds(26, 73, 109, 23); 
		getContentPane().add(rdbtnZRaporu);
		
		final JRadioButton rdbtnParametreYukle = new JRadioButton("Parametre Yukle");
		rdbtnParametreYukle.setBounds(26, 47, 109, 23);
		getContentPane().add(rdbtnParametreYukle);
		
		final JRadioButton rdbtnXRaporu = new JRadioButton("X Raporu");
		rdbtnXRaporu.setBounds(26, 99, 109, 23);
		getContentPane().add(rdbtnXRaporu);
		
		final JRadioButton rdbtnMaliRapor = new JRadioButton("Mali Rapor");
		rdbtnMaliRapor.setBounds(26, 125, 109, 23);
		getContentPane().add(rdbtnMaliRapor);
		
		final JRadioButton rdbtnEkuRapor = new JRadioButton("EKU Rapor");
		rdbtnEkuRapor.setBounds(26, 151, 109, 23);
		getContentPane().add(rdbtnEkuRapor);
		
		final JRadioButton rdbtnMaliKumulatifRapor = new JRadioButton("Mali Kumulatif Rapor");
		rdbtnMaliKumulatifRapor.setBounds(284, 47, 196, 23);
		getContentPane().add(rdbtnMaliKumulatifRapor);
		
		final JRadioButton rdbtnZRaporuGonder = new JRadioButton("Z Raporu Gonder");
		rdbtnZRaporuGonder.setBounds(284, 73, 145, 23);
		getContentPane().add(rdbtnZRaporuGonder);
		
		final JRadioButton rdbtnCekmeceAc = new JRadioButton("Cekmece Ac");
		rdbtnCekmeceAc.setBounds(284, 99, 132, 23);
		getContentPane().add(rdbtnCekmeceAc);
		
		final JRadioButton rdbtnBankaGunSonu = new JRadioButton("Banka Gun Sonu");
		rdbtnBankaGunSonu.setBounds(284, 125, 145, 23);
		getContentPane().add(rdbtnBankaGunSonu);
		
		final JRadioButton rdbtnBankaParametreYukle = new JRadioButton("Banka Parametre Yukle");
		rdbtnBankaParametreYukle.setBounds(284, 151, 159, 23);
		getContentPane().add(rdbtnBankaParametreYukle);
		
		ButtonGroup btnLocationGrp = new ButtonGroup();
		btnLocationGrp.add(rdbtnBankaGunSonu);
		btnLocationGrp.add(rdbtnBankaParametreYukle);
		btnLocationGrp.add(rdbtnCekmeceAc);
		btnLocationGrp.add(rdbtnEkuRapor);
		btnLocationGrp.add(rdbtnMaliKumulatifRapor);
		btnLocationGrp.add(rdbtnMaliRapor);
		btnLocationGrp.add(rdbtnParametreYukle);
		btnLocationGrp.add(rdbtnXRaporu);
		btnLocationGrp.add(rdbtnZRaporu);
		btnLocationGrp.add(rdbtnZRaporuGonder);
		
		lblFonksiyonlar = new JLabel("FONKS\u0130YONLAR");
		lblFonksiyonlar.setFont(new Font("Arial", Font.PLAIN, 15));
		lblFonksiyonlar.setBounds(26, 11, 454, 23);
		getContentPane().add(lblFonksiyonlar);
		btnOk.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				int retcode = Defines.TRAN_RESULT_OK;
				GmpDll.ST_FunctionParameters stFunctionParameters = new GmpDll.ST_FunctionParameters.ByReference();
				
				if(rdbtnCekmeceAc.isSelected())
				{
					retcode = gmpDriver.gmpDll.FiscalPrinter_FunctionOpenDrawer();
					
				}
				else if(rdbtnBankaGunSonu.isSelected())
				{
					retcode = gmpDriver.gmpDll.FiscalPrinter_FunctionBankingBatch(120 * 1000);
				}
				else if(rdbtnBankaParametreYukle.isSelected())
				{
					retcode = gmpDriver.gmpDll.FiscalPrinter_FunctionBankingParameter(120 * 1000);
				}
				else if(rdbtnParametreYukle.isSelected())
				{
					retcode = gmpDriver.gmpDll.FiscalPrinter_FunctionEcrParameter(120 * 1000);
				}
				else 
				{
					int eFunc = GmpDriver.FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR.getValue();
					if (PASS.equals(""))
                        return;
					
					stFunctionParameters.password.supervisor = PASS.getBytes();//stFunctionParameters.supervisorPASS = PASS.getBytes();
					
					
					if (!edtZ1.getText().equals(""))                      
						stFunctionParameters.start.ZNo = Integer.valueOf(edtZ1.getText());//stFunctionParameters.start_ZNo = Integer.valueOf(edtZ1.getText());
                    if (!edtZ2.getText().equals(""))                      
                    	stFunctionParameters.finish.ZNo = Integer.valueOf(edtZ2.getText());//stFunctionParameters.end_ZNo = Integer.valueOf(edtZ2.getText());
                    if (!edtFis1.getText().equals(""))
                    	stFunctionParameters.start.FNo = Integer.valueOf(edtFis1.getText());//stFunctionParameters.start_FNo = Integer.valueOf(edtFis1.getText());
                    if (!edtFis2.getText().equals(""))
                    	stFunctionParameters.finish.FNo = Integer.valueOf(edtFis2.getText());//stFunctionParameters.end_FNo = Integer.valueOf(edtFis2.getText());
                    if (!edtEkuNo.getText().equals(""))
                        stFunctionParameters.EKUNo = Integer.valueOf(edtEkuNo.getText());
					
					
					if (chckbxIsDate.isSelected())
					{
						ZonedDateTime zonedDateTime = ZonedDateTime.now();
						
						stFunctionParameters.start.date.day     = (byte)model.getDay();
	                    stFunctionParameters.start.date.month   = (byte)  model.getMonth();
	                    stFunctionParameters.start.date.year    = (short) model.getYear();
	                    stFunctionParameters.start.time.hour 	= (byte)zonedDateTime.getHour();
	                    stFunctionParameters.start.time.minute 	= (byte)zonedDateTime.getMinute();
	                    stFunctionParameters.start.time.second 	= (byte)zonedDateTime.getSecond();
	                    stFunctionParameters.finish.date.day 	= (byte)model2.getDay();
	                    stFunctionParameters.finish.date.month	= (byte)model2.getMonth();
	                    stFunctionParameters.finish.date.year 	= (short) model2.getYear();
	                    stFunctionParameters.finish.time.hour 	= (byte)zonedDateTime.getHour();
	                    stFunctionParameters.finish.time.minute = (byte)zonedDateTime.getMinute();
	                    stFunctionParameters.finish.time.second = (byte)zonedDateTime.getSecond();
						  
					}
					

					if(rdbtnZRaporu.isSelected())
					{
						eFunc = GmpDriver.FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR.getValue();
						
					}
					else if(rdbtnXRaporu.isSelected())
					{
						eFunc = GmpDriver.FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_X_RAPOR.getValue();
					}
					else if(rdbtnMaliRapor.isSelected())
					{
						eFunc = GmpDriver.FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_MALI_RAPOR.getValue();
						
					}
					else if(rdbtnEkuRapor.isSelected())
					{
						eFunc = GmpDriver.FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_EKU_RAPOR.getValue();
						
					}
					else if(rdbtnMaliKumulatifRapor.isSelected())
					{
						eFunc = GmpDriver.FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_MALI_KUMULATIF.getValue();
						
					}
					else if(rdbtnZRaporuGonder.isSelected())
					{
						eFunc = GmpDriver.FunctionFlags.GMP_EXT_DEVICE_FUNC_BIT_Z_RAPOR_GONDER.getValue();
					}
					
					retcode = gmpDriver.gmpDll.FiscalPrinter_FunctionReports(eFunc, (ST_FunctionParameters.ByReference) stFunctionParameters, 120 * 1000);
					
				}
				ErrorClass.HandleErrorCode(retcode);
				 
			}
		});
		btnOk.setBounds(323, 362, 120, 31);
		getContentPane().add(btnOk);
		
		final JPanel pnlFisData = new JPanel();
		pnlFisData.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, SystemColor.menu));
		pnlFisData.setBounds(24, 197, 439, 153);
		getContentPane().add(pnlFisData);
		pnlFisData.setLayout(null);
		
		JLabel lblZ1 = new JLabel("Z1:");
		lblZ1.setBounds(10, 35, 46, 14);
		pnlFisData.add(lblZ1);
		
		edtZ1 = new JTextField();
		edtZ1.setBounds(71, 31, 101, 23);
		pnlFisData.add(edtZ1);
		edtZ1.setColumns(10);
		
		edtZ2 = new JTextField();
		edtZ2.setBounds(71, 65, 101, 23);
		pnlFisData.add(edtZ2);
		edtZ2.setColumns(10);
		
		JLabel lblZ2 = new JLabel("Z2:");
		lblZ2.setBounds(10, 69, 46, 14);
		pnlFisData.add(lblZ2);
		
		edtFis1 = new JTextField();
		edtFis1.setBounds(329, 31, 76, 23);
		pnlFisData.add(edtFis1);
		edtFis1.setColumns(10);
		
		edtFis2 = new JTextField();
		edtFis2.setBounds(329, 65, 76, 23);
		pnlFisData.add(edtFis2);
		edtFis2.setColumns(10);
		
		edtEkuNo = new JTextField();
		edtEkuNo.setBounds(329, 105, 76, 23);
		pnlFisData.add(edtEkuNo);
		edtEkuNo.setColumns(10);
		
		JLabel lblEkuNo = new JLabel("Eku No:");
		lblEkuNo.setBounds(268, 109, 46, 14);
		pnlFisData.add(lblEkuNo);
		
		JLabel lblFis2 = new JLabel("Fis2:");
		lblFis2.setBounds(268, 69, 46, 14);
		pnlFisData.add(lblFis2);
		
		JLabel lblFis1 = new JLabel("Fis 1:");
		lblFis1.setBounds(268, 35, 46, 14);
		pnlFisData.add(lblFis1);
		
		chckbxIsDate = new JCheckBox("Tarihle Islem Etkinlestir");
		chckbxIsDate.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent arg0) {
				
				if(chckbxIsDate.isSelected())
				{
					pnlFisData.setVisible(false);
					pnlDateData.setVisible(true);
				}
				else
				{
					pnlFisData.setVisible(true);
					pnlDateData.setVisible(false);
				}
				
			}
		});
		chckbxIsDate.setBounds(26, 366, 159, 23);
		getContentPane().add(chckbxIsDate);
		
		pnlDateData = new JPanel();
		pnlDateData.setBounds(24, 197, 439, 153);
		getContentPane().add(pnlDateData);
		pnlDateData.setLayout(null);
		pnlDateData.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, SystemColor.menu));
		
		JLabel lblTarih1 = new JLabel("Tarih 1:");
		lblTarih1.setBounds(10, 36, 57, 14);
		pnlDateData.add(lblTarih1);
		
		JLabel lblTarih2 = new JLabel("Tarih 2:");
		lblTarih2.setBounds(10, 70, 57, 14);
		pnlDateData.add(lblTarih2);
		
		/*JFormattedTextField edtFormattedDate1 = new JFormattedTextField();
		edtFormattedDate1.setBounds(159, 33, 198, 20);
		pnlDateData.add(edtFormattedDate1);
		*/
		model = new UtilDateModel();
		Properties p = new Properties();
		p.put("text.today", "Today");
		p.put("text.month", "Month");
		p.put("text.year", "Year");
		JDatePanelImpl datePanel = new JDatePanelImpl(model,p);
		JDatePickerImpl datePicker = new JDatePickerImpl(datePanel, new DateComponentFormatter()); 
		datePicker.setBounds(80, 33, 198, 30);
		 
		pnlDateData.add(datePicker);
		
		/*
		JFormattedTextField edtFormattedDate2 = new JFormattedTextField();
		edtFormattedDate2.setBounds(159, 67, 198, 20);
		pnlDateData.add(edtFormattedDate2);*/
		
		model2 = new UtilDateModel();
		JDatePanelImpl datePanel2 = new JDatePanelImpl(model2,p);
		JDatePickerImpl datePicker2 = new JDatePickerImpl(datePanel2, new DateComponentFormatter());
		datePicker2.setBounds(80, 67, 198, 30);
		 
		pnlDateData.add(datePicker2);
		
		pnlFisData.setVisible(true);
		pnlDateData.setVisible(false);
	}
}
