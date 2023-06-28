package gui;

import db.TravelBookingConnection;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.sql.SQLException;
import java.sql.Statement;

public class MainWindow extends JFrame {
    private JButton personButton;
    private JButton guideButton;
    private JButton companyButton;
    private Statement st;

    public MainWindow() {
        initializeComponents();
        setupLayout();
        setupListeners();
        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent we)
            {
/*
                try {
                    st.execute("DROP VIEW select_car");
                    st.execute("DROP VIEW select_car_rental");
                    st.execute("DROP VIEW select_accommodation");
                    st.execute("DROP VIEW select_bus");
                    st.execute("DROP VIEW select_flight");
                }
                catch (SQLException ex) {
                    ex.printStackTrace();
                }

 */
                System.exit(0);

            }
        });
        setSize(600, 600);
        setLocationRelativeTo(null);
        setVisible(true);
        try {
            st = TravelBookingConnection.getConnection().createStatement();
            /*st.execute("CREATE VIEW select_car AS" +
                    " SELECT car_id,company_id,car_properties,daily_price FROM car;");
            st.execute("CREATE VIEW select_car_rental AS SELECT * FROM car_rental;");
            st.execute("CREATE VIEW select_accommodation AS SELECT * FROM accommodation;");
            st.execute("CREATE VIEW select_bus AS SELECT * FROM bus;");
            st.execute("CREATE VIEW select_flight AS SELECT * FROM flight;");
*/
        }
        catch (SQLException ex) {
            ex.printStackTrace();
        }

    }

    private void initializeComponents() {
        personButton = new JButton("Person View");
        guideButton = new JButton("Guide View");
        companyButton = new JButton("Company View");
    }

    private void setupLayout() {
        setLayout(new GridLayout(3, 1));
        add(personButton);
        add(guideButton);
        add(companyButton);
    }

    private void setupListeners() {
        personButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openPersonView();
            }
        });

        guideButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openGuideView();
            }
        });
        companyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                openCompanyView();
            }
        });
    }

    private void openPersonView() {
        PersonView personView = new PersonView();
        personView.setVisible(true);
    }

    private void openGuideView() {
        GuideView guideView = new GuideView();
        guideView.setVisible(true);
    }

    private void openCompanyView() {
        CompanyView companyView = new CompanyView();
        companyView.setVisible(true);
    }
}
