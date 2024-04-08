// -*- Mode: Java -*-

/*---------------------------- BEGIN LICENSE BLOCK ---------------------------+
 |                                                                            |
 | Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          |
 |                                                                            |
 | The contents of this file are subject to the Mozilla Public License        |
 | Version 1.1 (the "License"); you may not use this file except in           |
 | compliance with the License. You may obtain a copy of the License at       |
 | http://www.mozilla.org/MPL/                                                |
 |                                                                            |
 | Software distributed under the License is distributed on an "AS IS" basis, |
 | WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   |
 | for the specific language governing rights and limitations under the       |
 | License.                                                                   |
 |                                                                            |
 | The Original Code is the PowerLoom KR&R System.                            |
 |                                                                            |
 | The Initial Developer of the Original Code is                              |
 | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
 | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
 |                                                                            |
 | Portions created by the Initial Developer are Copyright (C) 2002-2010      |
 | the Initial Developer. All Rights Reserved.                                |
 |                                                                            |
 | Contributor(s):                                                            |
 |                                                                            |
 | Alternatively, the contents of this file may be used under the terms of    |
 | either the GNU General Public License Version 2 or later (the "GPL"), or   |
 | the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   |
 | in which case the provisions of the GPL or the LGPL are applicable instead |
 | of those above. If you wish to allow use of your version of this file only |
 | under the terms of either the GPL or the LGPL, and not to allow others to  |
 | use your version of this file under the terms of the MPL, indicate your    |
 | decision by deleting the provisions above and replace them with the notice |
 | and other provisions required by the GPL or the LGPL. If you do not delete |
 | the provisions above, a recipient may use your version of this file under  |
 | the terms of any one of the MPL, the GPL or the LGPL.                      |
 |                                                                            |
 +----------------------------- END LICENSE BLOCK ---------------------------*/


// Version: $Id$

package edu.isi.powerloom.gui.components;

import java.awt.event.*;
import java.util.*;
import edu.isi.powerloom.gui.xmlobject.*;
import edu.isi.powerloom.gui.serverinterface.*;

/**
 * Frame for Console window.
 *
 * @author <a href=mailto:eric@metrotech-consulting.com>Eric Melz</a>
 * @since October 11, 2002, 11:41 AM
 */
public class ConsoleFrame extends PLFrame {
    
    /** Creates new form ConsoleFrame */
    public ConsoleFrame() {
        initComponents();
	initCustomComponents();
	initialize();
    }
    
    private void initCustomComponents() {
	String[] types = {"Text Holder"};
        consolePane = new ConsolePanel(this, "Console Panel", Arrays.asList(types));
        jScrollPane1.setViewportView(consolePane);
    }

    private void initialize() {
	try {
	    app = PowerloomApp.getInstance();
            edu.isi.powerloom.gui.xmlobject.PLSurrogateContainer modules = 
		    KnowledgeManager.getInstance().getModules().listifyTreeContainer();
            PLListModel model = new PLListModel(null, modules);
            moduleComboBox.setModel(model);
	    moduleComboBox.addItemListener(new ItemListener () {
		    public void itemStateChanged(ItemEvent e) {
			consolePane.setModule((PLModule)moduleComboBox.getSelectedItem());
			app.setMostRecentlyTouchedModule((PLModule)moduleComboBox.getSelectedItem());
		    }
		});
            PLModule selectedModule = app.getMostRecentlyTouchedModule();
            setModule(selectedModule);
	} catch (Exception e) {
	    PowerloomApp.getInstance().handleException(e);
	}
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        jButton2 = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        jTextArea1 = new javax.swing.JTextArea();
        jPanel1 = new javax.swing.JPanel();
        jPanel2 = new javax.swing.JPanel();
        moduleComboBox = new javax.swing.JComboBox();
        jPanel3 = new javax.swing.JPanel();
        cancelButton = new javax.swing.JButton();

        jButton2.setText("jButton2");

        setClosable(true);
        setIconifiable(true);
        setMaximizable(true);
        setResizable(true);
        setTitle("Powerloom Console");
        jScrollPane1.setViewportView(jTextArea1);

        getContentPane().add(jScrollPane1, java.awt.BorderLayout.CENTER);

        jPanel1.setLayout(new java.awt.BorderLayout());

        moduleComboBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                moduleComboBoxActionPerformed(evt);
            }
        });

        jPanel2.add(moduleComboBox);

        jPanel1.add(jPanel2, java.awt.BorderLayout.NORTH);

        cancelButton.setText("Cancel");
        cancelButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                cancelButtonActionPerformed(evt);
            }
        });

        jPanel3.add(cancelButton);

        jPanel1.add(jPanel3, java.awt.BorderLayout.SOUTH);

        getContentPane().add(jPanel1, java.awt.BorderLayout.SOUTH);

        pack();
        java.awt.Dimension screenSize = java.awt.Toolkit.getDefaultToolkit().getScreenSize();
        setSize(new java.awt.Dimension(400, 300));
        setLocation((screenSize.width-400)/2,(screenSize.height-300)/2);
    }//GEN-END:initComponents

    private void cancelButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_cancelButtonActionPerformed
	doDefaultCloseAction();
    }//GEN-LAST:event_cancelButtonActionPerformed

    private void moduleComboBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_moduleComboBoxActionPerformed
        // Add your handling code here:
    }//GEN-LAST:event_moduleComboBoxActionPerformed

    public PLModule getModule() {
	return (PLModule)moduleComboBox.getSelectedItem();
    }    

    public void setModule(edu.isi.powerloom.gui.xmlobject.PLModule selectedModule) {
	if (selectedModule != null) {
            moduleComboBox.setSelectedItem(selectedModule);
	}
        consolePane.setModule(selectedModule);
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel jPanel3;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JButton jButton2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JComboBox moduleComboBox;
    private javax.swing.JTextArea jTextArea1;
    private javax.swing.JButton cancelButton;
    // End of variables declaration//GEN-END:variables
    private ExpressionEditorPanel consolePane;
    private PowerloomApp app;
}
