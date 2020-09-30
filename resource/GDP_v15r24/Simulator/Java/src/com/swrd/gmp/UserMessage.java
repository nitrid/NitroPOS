package com.swrd.gmp;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.JOptionPane;
import javax.swing.border.TitledBorder;
import javax.swing.UIManager;

import java.awt.Color;

import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.JLabel;

import java.awt.Font;

import javax.swing.JList;



import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class UserMessage extends JDialog {
	
	private JTextField txtTextToAdd;
	private JLabel lblInfo;
	private JList lstLines;
	GmpDriver gmpDriver;
	/**
	 * Launch the application.
	 */ 
	
	public int start() {
		
		ErrorClass.lblError = lblInfo;
		
		try {
			this.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			this.setModal(true);
			this.setVisible(true); 
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return 1;//lstBankList.getSelectedIndex();
		
	}

	/**
	 * Create the dialog.
	 */
	public UserMessage(GmpDriver gmpDriverObj) {
		
		gmpDriver = gmpDriverObj;
		
		setBounds(100, 100, 713, 390);
		getContentPane().setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Mesaj Tipi", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel.setBounds(10, 24, 161, 142);
		getContentPane().add(panel);
		panel.setLayout(null);
		
		JRadioButton rdbtnMsgTypeText = new JRadioButton("Text");
		rdbtnMsgTypeText.setBounds(18, 25, 109, 23);
		panel.add(rdbtnMsgTypeText);
		
		final JRadioButton rdbtnMsgTypeBarkod = new JRadioButton("Barkod");
		rdbtnMsgTypeBarkod.setBounds(18, 51, 109, 23);
		panel.add(rdbtnMsgTypeBarkod);
		
		final JRadioButton rdbtnMsgTypeQr = new JRadioButton("QR");
		rdbtnMsgTypeQr.setBounds(18, 77, 109, 23);
		panel.add(rdbtnMsgTypeQr);
		
		JPanel panel_1 = new JPanel();
		panel_1.setLayout(null);
		panel_1.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Font B\u00FCy\u00FCkl\u00FC\u011F\u00FC", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel_1.setBounds(181, 24, 161, 142);
		getContentPane().add(panel_1);
		
		final JRadioButton rdbtnFontSize12 = new JRadioButton("12");
		rdbtnFontSize12.setBounds(18, 25, 109, 23);
		panel_1.add(rdbtnFontSize12);
		
		final JRadioButton rdbtnFontSize24 = new JRadioButton("24");
		rdbtnFontSize24.setBounds(18, 51, 109, 23);
		panel_1.add(rdbtnFontSize24);
		
		final JRadioButton rdbtnFontSize32 = new JRadioButton("32");
		rdbtnFontSize32.setBounds(18, 77, 109, 23);
		panel_1.add(rdbtnFontSize32);
		
		final JRadioButton rdbtnFontSize48 = new JRadioButton("48");
		rdbtnFontSize48.setBounds(18, 105, 109, 23);
		panel_1.add(rdbtnFontSize48);
		
		JPanel panel_2 = new JPanel();
		panel_2.setLayout(null);
		panel_2.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Se\u00E7enek", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel_2.setBounds(10, 181, 161, 142);
		getContentPane().add(panel_2);
		
		final JRadioButton rdbtnOptionNormal = new JRadioButton("Normal");
		rdbtnOptionNormal.setBounds(18, 25, 109, 23);
		panel_2.add(rdbtnOptionNormal);
		
		final JRadioButton rdbtnOptionBold = new JRadioButton("Bold");
		rdbtnOptionBold.setBounds(18, 51, 109, 23);
		panel_2.add(rdbtnOptionBold);
		
		final JRadioButton rdbtnOptionInverted = new JRadioButton("Inverted");
		rdbtnOptionInverted.setBounds(18, 77, 109, 23);
		panel_2.add(rdbtnOptionInverted);
		
		JPanel panel_3 = new JPanel();
		panel_3.setLayout(null);
		panel_3.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Konum", TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 0, 0)));
		panel_3.setBounds(181, 181, 161, 142);
		getContentPane().add(panel_3);
		
		final JRadioButton rdbtnLeft = new JRadioButton("Sol");
		rdbtnLeft.setBounds(18, 25, 109, 23);
		panel_3.add(rdbtnLeft);
		
		final JRadioButton rdbtnMiddle = new JRadioButton("Orta");
		rdbtnMiddle.setBounds(18, 51, 109, 23);
		panel_3.add(rdbtnMiddle);
		
		final JRadioButton rdbtnRight = new JRadioButton("Sag");
		rdbtnRight.setBounds(18, 77, 109, 23);
		panel_3.add(rdbtnRight);
		
		txtTextToAdd = new JTextField();
		txtTextToAdd.setBounds(359, 52, 232, 23);
		getContentPane().add(txtTextToAdd);
		txtTextToAdd.setColumns(10);
		 
		final DefaultListModel listModel = new DefaultListModel(); 
		
		JButton btnAdd = new JButton("Ekle");
		btnAdd.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				int flag=0;

	            if( txtTextToAdd.getText().length() > 48 )
	            {
	            	JOptionPane.showMessageDialog(null,"Mesaj Alaný 48 karakterden fazla olamaz");
		            return;
	            }

                if (rdbtnMsgTypeQr.isSelected()) flag |= Defines.PS_QRCODE;
                else if (rdbtnMsgTypeBarkod.isSelected()) flag |= Defines.PS_BARCODE;

                if (rdbtnFontSize12.isSelected()) flag |= Defines.PS_12;
                else if (rdbtnFontSize24.isSelected()) flag |= Defines.PS_24;
                else if (rdbtnFontSize32.isSelected()) flag |= Defines.PS_32;
                else if (rdbtnFontSize48.isSelected()) flag |= Defines.PS_48;

                if (rdbtnOptionBold.isSelected()) flag |= Defines.PS_BOLD;
                else if (rdbtnOptionInverted.isSelected()) flag |= Defines.PS_INVERTED;

                if (rdbtnMiddle.isSelected()) flag |= Defines.PS_CENTER;
                else if (rdbtnRight.isSelected()) flag |= Defines.PS_RIGHT;
 
                listModel.addElement("0x" + String.format("%8s", Integer.toHexString(flag)).replace(' ', '0')+ "=>" + txtTextToAdd.getText()); 
			}
		});
		btnAdd.setBounds(598, 51, 89, 23);
		getContentPane().add(btnAdd);
		
		JButton btnPrint = new JButton("Yazd\u0131r");
		btnPrint.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				GmpDll.ST_USER_MESSAGE[] stUserMessage = new GmpDll.ST_USER_MESSAGE[40];
				for(int i = 0 ; i < 40; i++)
				{
					stUserMessage[i] = new GmpDll.ST_USER_MESSAGE();			
				}
	            int numberOfUserMessages = 0;          

	            numberOfUserMessages = listModel.getSize();
	            for (int i = 0; i < numberOfUserMessages; i++)
	            {
	            	String[] data = ((String)listModel.getElementAt(i)).substring(2).split("=>");
	            	
	            	stUserMessage[i].flag = Integer.parseInt(data[0], 16);
	            	stUserMessage[i].len  = (byte) data[1].length();
	            	stUserMessage[i].message  = data[1].getBytes();
	            }
  
	            int retcode = Defines.TRAN_RESULT_OK;

	            retcode = gmpDriver.FiscalPrinter_PrintUserMessage(stUserMessage, (short)numberOfUserMessages, gmpDriver.gstTicket, gmpDriver.TIMEOUT_DEFAULT);

	            if (retcode != Defines.TRAN_RESULT_OK)
	                ErrorClass.HandleErrorCode(retcode); 
				
			}
		});
		btnPrint.setBounds(598, 300, 89, 23);
		getContentPane().add(btnPrint);
		
		lblInfo = new JLabel("KULLANICI MESAJI");
		lblInfo.setFont(new Font("Arial", Font.PLAIN, 15));
		lblInfo.setBounds(359, 19, 328, 23);
		getContentPane().add(lblInfo);
		
		lstLines = new JList(listModel);
		lstLines.setBorder(new TitledBorder(null, "", TitledBorder.LEADING, TitledBorder.TOP, null, null));
		lstLines.setBounds(359, 107, 328, 169);
		getContentPane().add(lstLines);
		
		ButtonGroup btnMsgTypGrp = new ButtonGroup();
		btnMsgTypGrp.add(rdbtnMsgTypeText);
		btnMsgTypGrp.add(rdbtnMsgTypeBarkod);
		btnMsgTypGrp.add(rdbtnMsgTypeQr);
		
		ButtonGroup btnFontSizeGroup = new ButtonGroup();
		btnFontSizeGroup.add(rdbtnFontSize12);
		btnFontSizeGroup.add(rdbtnFontSize24);
		btnFontSizeGroup.add(rdbtnFontSize32);
		btnFontSizeGroup.add(rdbtnFontSize48);
		
		ButtonGroup btnOptionGrp = new ButtonGroup();
		btnOptionGrp.add(rdbtnOptionNormal);
		btnOptionGrp.add(rdbtnOptionBold);
		btnOptionGrp.add(rdbtnOptionInverted);
		
		ButtonGroup btnLocationGrp = new ButtonGroup();
		btnLocationGrp.add(rdbtnLeft);
		btnLocationGrp.add(rdbtnMiddle);
		btnLocationGrp.add(rdbtnRight); 
		
		rdbtnMsgTypeText.setSelected(true);
		rdbtnMiddle.setSelected(true);
		rdbtnFontSize24.setSelected(true);
		rdbtnOptionNormal.setSelected(true);
		
	}
}
