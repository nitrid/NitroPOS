package com.swrd.gmp;

import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JComboBox;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class Discount extends JDialog {

	private final JPanel contentPanel = new JPanel();
	private final JComboBox cmbDiscType = new JComboBox(GmpDriver.EDiscountType.values());
	private JTextField txtIndexOfItem;

	GmpDriver gmpDriver;	
	/**
	 * Launch the application.
	 */ 
	
	public int start() {
		try {
			this.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			this.setModal(true);
			this.setVisible(true); 
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		return 1;//lstBankList.getSelectedIndex();
		
	}/**/

	/**
	 * Create the dialog.
	 */
	public Discount(GmpDriver gmpDriverObj) {
		setTitle("Indirim");
		setBounds(100, 100, 450, 300);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		cmbDiscType.setBounds(60, 44, 298, 31);
		contentPanel.add(cmbDiscType); 
		
		final JTextField txtDiscValue = new JTextField();
		txtDiscValue.setBounds(192, 141, 166, 39);
		contentPanel.add(txtDiscValue);
		
		JButton btnNewButton = new JButton("Islemi Baslat");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				 
					gmpDriver.RaiseAndDiscount(Short.valueOf(txtIndexOfItem.getText()), cmbDiscType.getSelectedIndex(), txtDiscValue.getText()); 
					Discount.this.dispose();
			}
		});
		btnNewButton.setBounds(236, 195, 122, 39);
		contentPanel.add(btnNewButton);
		
		txtIndexOfItem = new JTextField();
		txtIndexOfItem.setBounds(192, 91, 166, 39);
		contentPanel.add(txtIndexOfItem);
		
		JLabel lblNewLabel = new JLabel("Item Index");
		lblNewLabel.setBounds(60, 103, 104, 14);
		contentPanel.add(lblNewLabel);
		
		
		JLabel lblAmountrate = new JLabel("Amount/Rate");
		lblAmountrate.setBounds(60, 153, 104, 14);
		contentPanel.add(lblAmountrate);
		

		gmpDriver = gmpDriverObj;
	}

}


