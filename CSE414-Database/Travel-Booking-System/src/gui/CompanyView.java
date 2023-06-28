package gui;

import db.TravelBookingConnection;
import models.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.Inet4Address;
import java.sql.*;

public class CompanyView extends JFrame {
    private JButton viewCarButton;
    private JButton viewCarRentalButton;
    private JButton viewPersonButton;
    private JButton viewAccommodationButton;
    private JButton viewHotelButton;
    private JButton viewRoomButton;
    private JButton viewFlightButton;
    private JButton viewBusButton;
    private JButton viewTransportButton;
    private JButton viewCompanyButton;
    private JButton viewTourButton;
    private JButton viewGuideButton;
    private JButton transferGuideButton;
    private JButton transferCarRentalButton;
    private Statement st;



    public CompanyView() {
        initializeComponents();
        setupLayout();
        setupListeners();
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setTitle("Company View");
        setSize(600, 600);
        setLocationRelativeTo(null);
        try {
            st = TravelBookingConnection.getConnection().createStatement();
        }
        catch (SQLException ex) {
            ex.printStackTrace();
        }
    }
    private void initializeComponents() {
        viewCarButton=new JButton("Car Table");
        viewCarRentalButton=new JButton("Car Rental Table");
        viewPersonButton=new JButton("Person Table");
        viewAccommodationButton=new JButton("Accommodation Table");
        viewHotelButton=new JButton("Hotel Table");
        viewRoomButton=new JButton("Room Table");
        viewFlightButton=new JButton("Flight Table");
        viewBusButton=new JButton("Bus Table");
        viewTransportButton=new JButton("Transport Table");
        viewCompanyButton=new JButton("Company Table");
        viewTourButton=new JButton("Tour Table");
        viewGuideButton=new JButton("Guide Table");
        transferGuideButton=new JButton("Transfer Guide");
        transferCarRentalButton=new JButton("Transfer Car Rental");
    }
    private void setupLayout() {
        setLayout(new GridLayout(7,2));
        add(viewCarButton);
        add(viewCarRentalButton);
        add(viewPersonButton);
        add(viewAccommodationButton);
        add(viewHotelButton);
        add(viewRoomButton);
        add(viewFlightButton);
        add(viewBusButton);
        add(viewTransportButton);
        add(viewCompanyButton);
        add(viewTourButton);
        add(viewGuideButton);
        add(transferGuideButton);
        add(transferCarRentalButton);

    }
    private void setupListeners() {
        viewCarButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewCar();
            }
        });

        viewCarRentalButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewCarRental();
            }
        });

        viewPersonButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewPerson();
            }
        });

        viewAccommodationButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewAccommodation();
            }
        });

        viewHotelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewHotel();
            }
        });

        viewRoomButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewRoom();
            }
        });

        viewFlightButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewFlight();
            }
        });

        viewBusButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewBus();
            }
        });

        viewTransportButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewTransport();
            }
        });

        viewCompanyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewCompany();
            }
        });

        viewTourButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewTour();
            }
        });

        viewGuideButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewGuide();
            }
        });
        transferGuideButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                transferGuide();
            }
        });
        transferCarRentalButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                transferCarRental();
            }
        });

    }

    private void viewCar() {
        try {
            // Implement the logic for viewing the car table
            String company_id = JOptionPane.showInputDialog(this, "Enter company_id:", "View cars",
                    JOptionPane.QUESTION_MESSAGE);


            String query = "SELECT * FROM car WHERE company_id = "+company_id;
            ResultSet resultSet = st.executeQuery(query);


            // Check if there are any car entries for the specified company_id
            if (!resultSet.isBeforeFirst()) {
                JOptionPane.showMessageDialog(this, "No car entries found for Company ID: " + company_id,
                        "Car View", JOptionPane.INFORMATION_MESSAGE);
                return;
            }


            // Create a table model to hold the car data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the accommodation table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add car rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the accommodation table model
            JTable carTable = new JTable(tableModel);

            // Create a panel to hold the car table
            JPanel carPanel = new JPanel(new BorderLayout());
            carPanel.add(new JScrollPane(carTable), BorderLayout.CENTER);

            JPanel buttonPanel = new JPanel(new BorderLayout());
            JButton insertButton = new JButton("Insert");
            JButton updateButton = new JButton("Update");
            JButton deleteButton = new JButton("Delete");

            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputTakePanel = new JPanel(new GridLayout());
                    JLabel car_id_label = new JLabel("car_id");
                    JLabel car_properties_label = new JLabel("car_properties");
                    JLabel daily_price_label = new JLabel("daily_price");

                    JTextField car_id = new JTextField();
                    JTextField car_properties = new JTextField();
                    JTextField daily_price = new JTextField();


                    inputTakePanel.setLayout(new GridLayout(4,3));
                    inputTakePanel.add(car_id_label);
                    inputTakePanel.add(car_id);
                    inputTakePanel.add(car_properties_label);
                    inputTakePanel.add(car_properties);
                    inputTakePanel.add(daily_price_label);
                    inputTakePanel.add(daily_price);


                    int result = JOptionPane.showConfirmDialog(null, inputTakePanel,
                            "Enter Car info", JOptionPane.OK_CANCEL_OPTION);

                    if(result == JOptionPane.OK_OPTION) {
                        try {
                            String query = "INSERT INTO car (car_id, company_id, car_properties, daily_price) " +
                                    "VALUES ("+car_id.getText()+", "+company_id+", '"+car_properties.getText()+"', "+daily_price.getText()+");";
                            System.out.println(query);
                            st.executeUpdate(query);
                            JOptionPane.showMessageDialog(CompanyView.this,"Insertion successful");

                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on insert "+ex.getMessage(), "View cars",
                                    JOptionPane.QUESTION_MESSAGE);
                        }
                    }

                }
            });

            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputTakePanel = new JPanel(new GridLayout());
                    JLabel car_id_label = new JLabel("car_id");
                    JLabel car_properties_label = new JLabel("car_properties");
                    JLabel daily_price_label = new JLabel("daily_price");

                    JTextField car_id = new JTextField();
                    JTextField car_properties = new JTextField();
                    JTextField daily_price = new JTextField();


                    inputTakePanel.setLayout(new GridLayout(4,3));
                    inputTakePanel.add(car_id_label);
                    inputTakePanel.add(car_id);
                    inputTakePanel.add(car_properties_label);
                    inputTakePanel.add(car_properties);
                    inputTakePanel.add(daily_price_label);
                    inputTakePanel.add(daily_price);

                    int result = JOptionPane.showConfirmDialog(CompanyView.this,inputTakePanel,"Enter car info",
                            JOptionPane.OK_CANCEL_OPTION);

                    if(result==JOptionPane.OK_OPTION) {
                        try {
                            Car car=new Car(Integer.parseInt(car_id.getText()),Integer.parseInt(company_id),car_properties.getText(),Integer.parseInt(daily_price.getText()));
                            String query = car.getUpdateQuery(car,Integer.parseInt(car_id.getText()));
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this, "Error on update ", "View cars",
                                        JOptionPane.QUESTION_MESSAGE);
                            }


                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on update "+ex.getMessage(), "View cars",
                                    JOptionPane.QUESTION_MESSAGE);
                        }
                    }

                }
            });

            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputTakePanel = new JPanel(new GridLayout());
                    JLabel car_id_label = new JLabel("car_id");

                    JTextField car_id = new JTextField();

                    inputTakePanel.setLayout(new GridLayout(1,2));
                    inputTakePanel.add(car_id_label);
                    inputTakePanel.add(car_id);

                    int result =  JOptionPane.showConfirmDialog(CompanyView.this,inputTakePanel,"Enter car info",
                            JOptionPane.OK_CANCEL_OPTION);

                    if(result==JOptionPane.OK_OPTION) {
                        try{
                            Car car = new Car();
                            String query = car.getDeleteQuery(Integer.parseInt(car_id.getText()));
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this, "Error on delete ", "View cars",
                                        JOptionPane.QUESTION_MESSAGE);
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on delete "+ex.getMessage(), "View cars",
                                    JOptionPane.QUESTION_MESSAGE);
                        }
                    }

                }
            });

            buttonPanel.add(insertButton,BorderLayout.NORTH);
            buttonPanel.add(updateButton,BorderLayout.CENTER);
            buttonPanel.add(deleteButton,BorderLayout.SOUTH);

            JPanel bothPanel = new JPanel(new BorderLayout());
            bothPanel.add(carPanel,BorderLayout.NORTH);
            bothPanel.add(buttonPanel,BorderLayout.SOUTH);


            // Display the accommodation table in a dialog
            JOptionPane.showMessageDialog(this, bothPanel, "Car Entries",
                    JOptionPane.PLAIN_MESSAGE);


        }
        catch (SQLException ex) {
            ex.printStackTrace();
        }

    }

    private void viewCarRental() {
        try {
            String company_id = JOptionPane.showInputDialog(this, "Enter company_id:", "View Car Rentals",
                    JOptionPane.QUESTION_MESSAGE);

            //String query = "SELECT rental_id, car_rental.car_id, person_id, start_date, end_date FROM car_rental,car WHERE car.company_id = " + company_id + " AND car.car_id = car_rental.car_id";
            String query = "SELECT DISTINCT car_rental.rental_id, car_rental.car_id, car_rental.person_id, car_rental.start_date, car_rental.end_date " +
                    "FROM car_rental " +
                    "RIGHT JOIN car ON car.car_id = car_rental.car_id " +
                    "WHERE car.company_id = " + company_id;

            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the car rental data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the car rental table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add car rental rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the car rental table model
            JTable carRentalTable = new JTable(tableModel);

            // Create a panel to hold the car rental table
            JPanel carRentalPanel = new JPanel(new BorderLayout());
            carRentalPanel.add(new JScrollPane(carRentalTable), BorderLayout.CENTER);

            // Create buttons for insert, update, and delete operations
            JButton insertButton = new JButton("Insert");
            JButton updateButton = new JButton("Update");
            JButton deleteButton = new JButton("Delete");

            // Insert button action listener
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Create input fields for car rental information
                    JTextField rentalIdField = new JTextField();
                    JTextField carIdField = new JTextField();
                    JTextField personIdField = new JTextField();
                    JTextField startDateField = new JTextField();
                    JTextField endDateField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Rental ID:"));
                    inputPanel.add(rentalIdField);
                    inputPanel.add(new JLabel("Car ID:"));
                    inputPanel.add(carIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Start Date:"));
                    inputPanel.add(startDateField);
                    inputPanel.add(new JLabel("End Date:"));
                    inputPanel.add(endDateField);

                    // Prompt the user for car rental information
                    int result = JOptionPane.showConfirmDialog(null, inputPanel,
                            "Enter Car Rental Information", JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String rentalId = rentalIdField.getText();
                        String carId = carIdField.getText();
                        String personId = personIdField.getText();
                        String startDate = startDateField.getText();
                        String endDate = endDateField.getText();

                        // TODO: Perform the insert operation with the retrieved information
                        // Execute the necessary SQL INSERT command using the retrieved values

                        CarRental carRental = new CarRental(
                                Integer.parseInt(rentalId),Integer.parseInt(carId),Integer.parseInt(personId),
                                Date.valueOf(startDate),Date.valueOf(endDate),Integer.parseInt(company_id)
                        );
                        try {
                            String query = carRental.getInsertQuery(carRental);
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insert successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insert error");
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Insert error" + ex.getMessage());

                        }


                    }
                }
            });

            // Update button action listener
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row index
                    int selectedRowIndex = carRentalTable.getSelectedRow();

                    // Make sure a row is selected
                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to update.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Retrieve the car rental information from the selected row
                    String rentalId = tableModel.getValueAt(selectedRowIndex, 0).toString();
                    String carId = tableModel.getValueAt(selectedRowIndex, 1).toString();
                    String personId = tableModel.getValueAt(selectedRowIndex, 2).toString();
                    String startDate = tableModel.getValueAt(selectedRowIndex, 3).toString();
                    String endDate = tableModel.getValueAt(selectedRowIndex, 4).toString();

                    // Create input fields and populate them with the retrieved information
                    JTextField rentalIdField = new JTextField(rentalId);
                    JTextField carIdField = new JTextField(carId);
                    JTextField personIdField = new JTextField(personId);
                    JTextField startDateField = new JTextField(startDate);
                    JTextField endDateField = new JTextField(endDate);

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Rental ID:"));
                    inputPanel.add(rentalIdField);
                    inputPanel.add(new JLabel("Car ID:"));
                    inputPanel.add(carIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Start Date:"));
                    inputPanel.add(startDateField);
                    inputPanel.add(new JLabel("End Date:"));
                    inputPanel.add(endDateField);

                    // Prompt the user for updated car rental information
                    int result = JOptionPane.showConfirmDialog(null, inputPanel,
                            "Update Car Rental Information", JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String updatedRentalId = rentalIdField.getText();
                        String updatedCarId = carIdField.getText();
                        String updatedPersonId = personIdField.getText();
                        String updatedStartDate = startDateField.getText();
                        String updatedEndDate = endDateField.getText();

                        // TODO: Perform the update operation with the retrieved information
                        // Execute the necessary SQL UPDATE command using the retrieved values

                        CarRental carRental = new CarRental(
                                Integer.parseInt(rentalId),Integer.parseInt(updatedCarId),Integer.parseInt(updatedPersonId),
                                Date.valueOf(updatedStartDate),Date.valueOf(updatedEndDate),Integer.parseInt(company_id)
                        );
                        try {
                            String query = carRental.getUpdateQuery(carRental,Integer.parseInt(updatedRentalId));
                            System.out.println(query);

                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update error");
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Update error " +ex.getMessage());

                        }
                    }
                }
            });

            // Delete button action listener
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row index
                    int selectedRowIndex = carRentalTable.getSelectedRow();

                    // Make sure a row is selected
                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to delete.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Retrieve the car rental information from the selected row
                    String rentalId = tableModel.getValueAt(selectedRowIndex, 0).toString();
                    String carId = tableModel.getValueAt(selectedRowIndex, 1).toString();
                    String personId = tableModel.getValueAt(selectedRowIndex, 2).toString();
                    String startDate = tableModel.getValueAt(selectedRowIndex, 3).toString();
                    String endDate = tableModel.getValueAt(selectedRowIndex, 4).toString();

                    // Create a confirmation dialog for the delete operation
                    int confirmation = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete this car rental entry?\n"
                                    + "Rental ID: " + rentalId + "\nCar ID: " + carId + "\nPerson ID: " + personId
                                    + "\nStart Date: " + startDate + "\nEnd Date: " + endDate,
                            "Delete Confirmation", JOptionPane.YES_NO_OPTION);

                    if (confirmation == JOptionPane.YES_OPTION) {
                        // TODO: Perform the delete operation
                        // Execute the necessary SQL DELETE command using the retrieved values
                        CarRental carRental = new CarRental(
                                Integer.parseInt(rentalId),Integer.parseInt(carId),Integer.parseInt(personId),
                                Date.valueOf(startDate),Date.valueOf(endDate),Integer.parseInt(company_id)
                        );
                        try {
                            String query = carRental.getDeleteQuery(Integer.parseInt(rentalId));
                            System.out.println(query);

                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete error");
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Delete error "+ex.getMessage());

                        }
                    }
                }
            });

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new GridLayout(1, 3));
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold the car rental table and buttons
            JPanel carRentalContentPanel = new JPanel(new BorderLayout());
            carRentalContentPanel.add(new JScrollPane(carRentalTable), BorderLayout.CENTER);
            carRentalContentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the car rental table and buttons in a dialog
            JOptionPane.showMessageDialog(this, carRentalContentPanel, "Car Rental Entries",
                    JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void viewPerson() {
        try {
            // Execute the SQL query to retrieve all person entries
            String query = "SELECT * FROM person";
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the person data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the person table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add person rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the person table model
            JTable personTable = new JTable(tableModel);

            // Create a panel to hold the person table
            JPanel personPanel = new JPanel(new BorderLayout());
            personPanel.add(new JScrollPane(personTable), BorderLayout.CENTER);

            // Create buttons for insert, update, and delete operations
            JButton insertButton = new JButton("Insert");
            JButton updateButton = new JButton("Update");
            JButton deleteButton = new JButton("Delete");

            // Insert button action listener
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputPanel = new JPanel(new GridLayout(4, 2));
                    inputPanel.add(new JLabel("Person ID:"));
                    JTextField personIdField = new JTextField();
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("First Name:"));
                    JTextField firstNameField = new JTextField();
                    inputPanel.add(firstNameField);
                    inputPanel.add(new JLabel("Birthdate:"));
                    JTextField ageField = new JTextField();
                    inputPanel.add(ageField);
                    inputPanel.add(new JLabel("Budget:"));
                    JTextField budgetField = new JTextField();
                    inputPanel.add(budgetField);


                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Person",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String personId = personIdField.getText();
                        String firstName = firstNameField.getText();
                        String age = ageField.getText();
                        String budget=budgetField.getText();

                        Date date = Date.valueOf(age);

                        // TODO: Perform the insert operation
                        // Execute the necessary SQL INSERT command with the retrieved values
                        try {
                            Person person = new Person(Integer.parseInt(personId),firstName,date,Integer.parseInt(budget));
                            String query = person.getInsertQuery(person);
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on insert "+ex.getMessage());
                        }
                    }
                }
            });

            // Update button action listener
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row index
                    int selectedRowIndex = personTable.getSelectedRow();

                    // Make sure a row is selected
                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to update.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Retrieve the person information from the selected row
                    String personId = tableModel.getValueAt(selectedRowIndex, 0).toString();
                    String firstName = tableModel.getValueAt(selectedRowIndex, 1).toString();
                    String age = tableModel.getValueAt(selectedRowIndex, 2).toString();
                    String budget = tableModel.getValueAt(selectedRowIndex,3).toString();

                    // Create an input panel with pre-filled data
                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Person ID:"));
                    JTextField personIdField = new JTextField(personId);
                    personIdField.setEditable(false);
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("First Name:"));
                    JTextField firstNameField = new JTextField(firstName);
                    inputPanel.add(firstNameField);
                    inputPanel.add(new JLabel("Birthdate:"));
                    JTextField ageField = new JTextField(age);
                    inputPanel.add(ageField);
                    inputPanel.add(new JLabel("Budget:"));
                    JTextField budgetField = new JTextField(budget);
                    inputPanel.add(budgetField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Person",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String updatedFirstName = firstNameField.getText();
                        String updatedAge = ageField.getText();
                        String updatedBudget = budgetField.getText();

                        // TODO: Perform the update operation
                        // Execute the necessary SQL UPDATE command with the updated values

                        try {
                            Person person = new Person(Integer.parseInt(personId),updatedFirstName,Date.valueOf(updatedAge),Integer.parseInt(updatedBudget));
                            String query = person.getUpdateQuery(person,Integer.parseInt(personId));
                            System.out.println(query);

                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update error");
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Update error "+ex.getMessage());

                        }

                    }
                }
            });

            // Delete button action listener
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row index
                    int selectedRowIndex = personTable.getSelectedRow();

                    // Make sure a row is selected
                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to delete.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Confirm the deletion
                    int confirmResult = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete this person?", "Confirm Deletion",
                            JOptionPane.YES_NO_OPTION);

                    if (confirmResult == JOptionPane.YES_OPTION) {
                        // Retrieve the person ID from the selected row
                        String personId = tableModel.getValueAt(selectedRowIndex, 0).toString();

                        // TODO: Perform the delete operation
                        // Execute the necessary SQL DELETE command using the person ID
                        Person person = new Person();
                        String query = person.getDeleteQuery(Integer.parseInt(personId));
                        System.out.println(query);
                        try {
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Delete error "+ex.getMessage());

                        }
                    }
                }
            });

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new FlowLayout());
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold the person table and buttons
            JPanel personContentPanel = new JPanel(new BorderLayout());
            personContentPanel.add(new JScrollPane(personTable), BorderLayout.CENTER);
            personContentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the person table and buttons in a dialog
            JOptionPane.showMessageDialog(this, personContentPanel, "Person Entries",
                    JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewAccommodation() {
        try {

            String companyID = JOptionPane.showInputDialog(this, "Enter company_id:", "View Accommodation",
                    JOptionPane.QUESTION_MESSAGE);

            // Construct the query to retrieve accommodations for the specified company
            String query = "SELECT * FROM accommodation WHERE company_id = " + companyID;
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the accommodation data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the accommodation table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add accommodation rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the accommodation table model
            JTable accommodationTable = new JTable(tableModel);

            // Insert button action listener
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputPanel = new JPanel(new GridLayout(7, 2));

                    inputPanel.add(new JLabel("Accommodation ID:"));
                    JTextField accommodationIdField = new JTextField();
                    inputPanel.add(accommodationIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIDField = new JTextField(companyID);
                    inputPanel.add(companyIDField);
                    inputPanel.add(new JLabel("Hotel ID:"));
                    JTextField hotelIdField = new JTextField();
                    inputPanel.add(hotelIdField);
                    inputPanel.add(new JLabel("Room ID:"));
                    JTextField roomIdField = new JTextField();
                    inputPanel.add(roomIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    JTextField personIdField = new JTextField();
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Check-in Date:"));
                    JTextField checkInDateField = new JTextField();
                    inputPanel.add(checkInDateField);
                    inputPanel.add(new JLabel("Check-out Date:"));
                    JTextField checkOutDateField = new JTextField();
                    inputPanel.add(checkOutDateField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Accommodation",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String accommodationId=accommodationIdField.getText();
                        String hotelId = hotelIdField.getText();
                        String roomId = roomIdField.getText();
                        String personId = personIdField.getText();
                        String checkInDate = checkInDateField.getText();
                        String checkOutDate = checkOutDateField.getText();

                        // TODO: Perform the insert operation
                        // Execute the necessary SQL INSERT command with the provided values
                        try {
                            Accommodation accommodation = new Accommodation(
                                    Integer.parseInt(accommodationId),Integer.parseInt(companyID),
                                    Integer.parseInt(hotelId),Integer.parseInt(roomId),
                                    Integer.parseInt(personId),
                                    Date.valueOf(checkInDate),Date.valueOf(checkOutDate)
                            );
                            String accommodationInsertQuery = accommodation.getInsertQuery(accommodation);
                            System.out.println(accommodationInsertQuery);
                            if(st.executeUpdate(accommodationInsertQuery)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on insert "+ex.getMessage());
                        }


                    }
                }
            });

            // Update button action listener
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = accommodationTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to update.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Retrieve the accommodation details from the selected row
                    String accommodationId = tableModel.getValueAt(selectedRowIndex, 0).toString();
                    String hotelId = tableModel.getValueAt(selectedRowIndex, 2).toString();
                    String roomId = tableModel.getValueAt(selectedRowIndex, 3).toString();
                    String personId = tableModel.getValueAt(selectedRowIndex, 4).toString();
                    String checkInDate = tableModel.getValueAt(selectedRowIndex, 5).toString();
                    String checkOutDate = tableModel.getValueAt(selectedRowIndex, 6).toString();

                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Hotel ID:"));
                    JTextField hotelIdField = new JTextField(hotelId);
                    inputPanel.add(hotelIdField);
                    inputPanel.add(new JLabel("Room ID:"));
                    JTextField roomIdField = new JTextField(roomId);
                    inputPanel.add(roomIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    JTextField personIdField = new JTextField(personId);
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Check-in Date:"));
                    JTextField checkInDateField = new JTextField(checkInDate);
                    inputPanel.add(checkInDateField);
                    inputPanel.add(new JLabel("Check-out Date:"));
                    JTextField checkOutDateField = new JTextField(checkOutDate);
                    inputPanel.add(checkOutDateField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Accommodation",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String updatedHotelId = hotelIdField.getText();
                        String updatedRoomId = roomIdField.getText();
                        String updatedPersonId = personIdField.getText();
                        String updatedCheckInDate = checkInDateField.getText();
                        String updatedCheckOutDate = checkOutDateField.getText();

                        // TODO: Perform the update operation
                        // Execute the necessary SQL UPDATE command with the updated values
                        try {
                            Accommodation accommodation = new Accommodation(
                                    Integer.parseInt(accommodationId),Integer.parseInt(companyID),
                                    Integer.parseInt(updatedHotelId),Integer.parseInt(updatedRoomId),
                                    Integer.parseInt(updatedPersonId),
                                    Date.valueOf(updatedCheckInDate),Date.valueOf(updatedCheckOutDate)
                            );
                            String accommodationUpdateQuery = accommodation.getUpdateQuery(accommodation,Integer.parseInt(accommodationId));

                            System.out.println(accommodationUpdateQuery);

                            if(st.executeUpdate(accommodationUpdateQuery)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update error");
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Update error "+ex.getMessage());

                        }
                    }
                }
            });

            // Delete button action listener
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = accommodationTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to delete.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    int confirmDialogResult = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete this accommodation?", "Confirm Delete",
                            JOptionPane.YES_NO_OPTION);

                    if (confirmDialogResult == JOptionPane.YES_OPTION) {
                        String accommodationId = tableModel.getValueAt(selectedRowIndex, 0).toString();

                        // TODO: Perform the delete operation
                        // Execute the necessary SQL DELETE command with the specified accommodation ID
                        Accommodation accommodation = new Accommodation();
                        String accommodationDeleteQuery = accommodation.getDeleteQuery(Integer.parseInt(accommodationId));
                        System.out.println(accommodationDeleteQuery);
                        try {
                            if(st.executeUpdate(accommodationDeleteQuery)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Delete error"+ex.getMessage());

                        }
                    }
                }
            });

            // Create a panel to hold the accommodation table
            JPanel accommodationPanel = new JPanel(new BorderLayout());
            accommodationPanel.add(new JScrollPane(accommodationTable), BorderLayout.CENTER);

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel();
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold both the accommodation table and the buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(accommodationPanel, BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the accommodation table and buttons in a dialog
            JOptionPane.showMessageDialog(this, contentPanel, "Accommodation Entries",
                    JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewHotel() {
        String companyID = JOptionPane.showInputDialog(this, "Enter company_id:", "View Hotel",
                JOptionPane.QUESTION_MESSAGE);

        try {
            // Construct the query to retrieve hotels for the specified company
            String query = "SELECT * FROM hotel WHERE company_id = " + companyID;
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the hotel data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the hotel table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add hotel rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the hotel table model
            JTable hotelTable = new JTable(tableModel);

            // Insert button action listener
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputPanel = new JPanel(new GridLayout(3, 2));
                    inputPanel.add(new JLabel("Hotel ID:"));
                    JTextField hotelIdField = new JTextField();
                    inputPanel.add(hotelIdField);
                    inputPanel.add(new JLabel("Name:"));
                    JTextField nameField = new JTextField();
                    inputPanel.add(nameField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyID);
                    inputPanel.add(companyIdField);



                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Hotel",
                            JOptionPane.OK_CANCEL_OPTION);



                    if (result == JOptionPane.OK_OPTION) {
                        String hotelId = hotelIdField.getText();
                        String companyId = companyIdField.getText();
                        String name = nameField.getText();

                        // TODO: Perform the insert operation
                        // Execute the necessary SQL INSERT command with the provided values
                        try {
                            Hotel hotel = new Hotel(Integer.parseInt(hotelId),name,Integer.parseInt(companyId));
                            String query = hotel.getInsertQuery(hotel);
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on insert "+ex.getMessage());
                        }
                    }
                }
            });

            // Update button action listener
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = hotelTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to update.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Retrieve the hotel details from the selected row
                    String hotelId = tableModel.getValueAt(selectedRowIndex, 0).toString();
                    String name = tableModel.getValueAt(selectedRowIndex, 1).toString();
                    String companyId = tableModel.getValueAt(selectedRowIndex, 2).toString();

                    JPanel inputPanel = new JPanel(new GridLayout(3, 2));
                    inputPanel.add(new JLabel("Hotel ID:"));
                    JTextField hotelIdField = new JTextField(hotelId);
                    inputPanel.add(hotelIdField);
                    inputPanel.add(new JLabel("Name:"));
                    JTextField nameField = new JTextField(name);
                    inputPanel.add(nameField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyId);
                    inputPanel.add(companyIdField);



                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Hotel",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String updatedHotelId = hotelIdField.getText();
                        String updatedCompanyId = companyIdField.getText();
                        String updatedName = nameField.getText();

                        // TODO: Perform the update operation
                        // Execute the necessary SQL UPDATE command with the updated values
                        try {
                            Hotel hotel = new Hotel(Integer.parseInt(updatedHotelId),updatedName,Integer.parseInt(updatedCompanyId));
                            String query = hotel.getUpdateQuery(hotel,Integer.parseInt(updatedHotelId));
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on update "+ex.getMessage());
                        }
                    }
                }
            });

            // Delete button action listener
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = hotelTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to delete.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    int confirmDialogResult = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete this hotel?", "Confirm Delete",
                            JOptionPane.YES_NO_OPTION);

                    if (confirmDialogResult == JOptionPane.YES_OPTION) {
                        String hotelId = tableModel.getValueAt(selectedRowIndex, 0).toString();


                        // TODO: Perform the delete operation
                        // Execute the necessary SQL DELETE command with the specified hotel ID
                        try {
                            Hotel hotel = new Hotel();
                            String query = hotel.getDeleteQuery(Integer.parseInt(hotelId));
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on delete "+ex.getMessage());
                        }
                    }
                }
            });

            // Create a panel to hold the hotel table
            JPanel hotelPanel = new JPanel(new BorderLayout());
            hotelPanel.add(new JScrollPane(hotelTable), BorderLayout.CENTER);

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel();
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold both the hotel table and the buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(hotelPanel, BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the hotel table and buttons in a dialog
            JOptionPane.showMessageDialog(this, contentPanel, "Hotel Entries",
                    JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewRoom() {
        String companyID = JOptionPane.showInputDialog(this, "Enter company_id:", "View Room",
                JOptionPane.QUESTION_MESSAGE);
        String hotelID = JOptionPane.showInputDialog(this, "Enter hotel_id:", "View Room",
                JOptionPane.QUESTION_MESSAGE);

        try {
            // Construct the query to retrieve rooms for the specified company and hotel
            //String query = "SELECT room_id,room.hotel_id,daily_price,room_properties FROM room,hotel WHERE company_id = " + companyID + " AND room.hotel_id = " + hotelID;
            String query = "SELECT room.room_id, room.hotel_id, room.daily_price, room.room_properties " +
                    "FROM room " +
                    "LEFT JOIN hotel ON room.hotel_id = hotel.hotel_id " +
                    "WHERE room.hotel_id = "+hotelID;
            System.out.println(query);
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the room data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the room table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add room rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the room table model
            JTable roomTable = new JTable(tableModel);

            // Insert button action listener
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Room ID:"));
                    JTextField roomIdField = new JTextField();
                    inputPanel.add(roomIdField);
                    inputPanel.add(new JLabel("Hotel ID:"));
                    JTextField hotelIdField = new JTextField(hotelID);
                    inputPanel.add(hotelIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyID);
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Daily Price:"));
                    JTextField dailyPriceField = new JTextField();
                    inputPanel.add(dailyPriceField);
                    inputPanel.add(new JLabel("Room Properties:"));
                    JTextField roomPropertiesField = new JTextField();
                    inputPanel.add(roomPropertiesField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Room",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String roomId = roomIdField.getText();
                        String hotelId = hotelIdField.getText();
                        String companyId = companyIdField.getText();
                        String dailyPrice = dailyPriceField.getText();
                        String roomProperties = roomPropertiesField.getText();

                        // TODO: Perform the insert operation
                        // Execute the necessary SQL INSERT command with the provided values

                        try {
                            Room room = new Room(Integer.parseInt(roomId),Integer.parseInt(hotelID) ,Integer.parseInt(dailyPrice),roomProperties);
                            String query = room.getInsertQuery(room);
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion error ");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on insert "+ex.getMessage());
                        }

                    }
                }
            });

            // Update button action listener
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = roomTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to update.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Retrieve the room details from the selected row
                    String roomId = tableModel.getValueAt(selectedRowIndex, 0).toString();
                    String hotelId = tableModel.getValueAt(selectedRowIndex, 1).toString();
                    String companyId = companyID;
                    String dailyPrice = tableModel.getValueAt(selectedRowIndex, 2).toString();
                    String roomProperties = tableModel.getValueAt(selectedRowIndex, 3).toString();

                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Room ID:"));
                    JTextField roomIdField = new JTextField(roomId);
                    inputPanel.add(roomIdField);
                    inputPanel.add(new JLabel("Hotel ID:"));
                    JTextField hotelIdField = new JTextField(hotelId);
                    inputPanel.add(hotelIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyId);
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Daily Price:"));
                    JTextField dailyPriceField = new JTextField(dailyPrice);
                    inputPanel.add(dailyPriceField);
                    inputPanel.add(new JLabel("Room Properties:"));
                    JTextField roomPropertiesField = new JTextField(roomProperties);
                    inputPanel.add(roomPropertiesField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Room",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String updatedRoomId = roomIdField.getText();
                        String updatedHotelId = hotelIdField.getText();
                        String updatedCompanyId = companyIdField.getText();
                        String updatedDailyPrice = dailyPriceField.getText();
                        String updatedRoomProperties = roomPropertiesField.getText();

                        // TODO: Perform the update operation
                        // Execute the necessary SQL UPDATE command with the updated values
                        try {
                            Room room = new Room(Integer.parseInt(updatedRoomId),Integer.parseInt(updatedHotelId) ,Integer.parseInt(updatedDailyPrice),updatedRoomProperties);
                            String query = room.getUpdateQuery(room,Integer.parseInt(updatedRoomId));
                            System.out.println(query);

                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update error");
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Update error "+ex.getMessage());

                        }
                    }
                }
            });

            // Delete button action listener
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = roomTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to delete.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    int confirmDialogResult = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete this room?", "Confirm Delete",
                            JOptionPane.YES_NO_OPTION);

                    if (confirmDialogResult == JOptionPane.YES_OPTION) {
                        String roomId = tableModel.getValueAt(selectedRowIndex, 0).toString();

                        // TODO: Perform the delete operation
                        // Execute the necessary SQL DELETE command with the specified room ID
                        Room room = new Room();
                        String query = room.getDeleteQuery(Integer.parseInt(roomId));
                        System.out.println(query);

                        try {
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Delete error "+ex.getMessage());

                        }
                    }
                }
            });

            // Create a panel to hold the room table
            JPanel roomPanel = new JPanel(new BorderLayout());
            roomPanel.add(new JScrollPane(roomTable), BorderLayout.CENTER);

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel();
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold both the room table and the buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(roomPanel, BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the room table and buttons in a dialog
            JOptionPane.showMessageDialog(this, contentPanel, "Room Entries",
                    JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void viewFlight() {
        String companyID = JOptionPane.showInputDialog(this, "Enter company_id:", "View Flight",
                JOptionPane.QUESTION_MESSAGE);

        try {
            // Construct the query to retrieve flights for the specified company
            Flight selectFlight = new Flight();
            String selectFlightCompany=selectFlight.getSelectQueryCompany(Integer.parseInt(companyID));
            ResultSet resultSet = st.executeQuery(selectFlightCompany);

            // Create a table model to hold the flight data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the flight table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add flight rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the flight table model
            JTable flightTable = new JTable(tableModel);

            // Insert button action listener
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Flight ID:"));
                    JTextField flightIdField = new JTextField();
                    inputPanel.add(flightIdField);
                    inputPanel.add(new JLabel("Guide ID:"));
                    JTextField guideIdField = new JTextField();
                    inputPanel.add(guideIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyID);
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Price:"));
                    JTextField priceField = new JTextField();
                    inputPanel.add(priceField);
                    inputPanel.add(new JLabel("Flight Info:"));
                    JTextField flightInfoField = new JTextField();
                    inputPanel.add(flightInfoField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Flight",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String flightId = flightIdField.getText();
                        String guideId = guideIdField.getText();
                        String companyId = companyIdField.getText();
                        String price = priceField.getText();
                        String flightInfo = flightInfoField.getText();

                        // TODO: Perform the insert operation
                        // Execute the necessary SQL INSERT command with the provided values
                        try {
                            Flight flight = new Flight(
                              Integer.parseInt(flightId),Integer.parseInt(guideId),
                              Integer.parseInt(companyId),Integer.parseInt(price),flightInfo
                            );
                            String query = flight.getInsertQuery(flight);
                            System.out.println(query);
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Insertion error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this, "Error on insert "+ex.getMessage());
                        }
                    }
                }
            });

            // Update button action listener
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = flightTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to update.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    // Retrieve the flight details from the selected row
                    String flightId = tableModel.getValueAt(selectedRowIndex, 0).toString();
                    String guideId = tableModel.getValueAt(selectedRowIndex, 1).toString();
                    String companyId = tableModel.getValueAt(selectedRowIndex, 2).toString();
                    String price = tableModel.getValueAt(selectedRowIndex, 3).toString();
                    String flightInfo = tableModel.getValueAt(selectedRowIndex, 4).toString();

                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Flight ID:"));
                    JTextField flightIdField = new JTextField(flightId);
                    inputPanel.add(flightIdField);
                    inputPanel.add(new JLabel("Guide ID:"));
                    JTextField guideIdField = new JTextField(guideId);
                    inputPanel.add(guideIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyId);
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Price:"));
                    JTextField priceField = new JTextField(price);
                    inputPanel.add(priceField);
                    inputPanel.add(new JLabel("Flight Info:"));
                    JTextField flightInfoField = new JTextField(flightInfo);
                    inputPanel.add(flightInfoField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Flight",
                            JOptionPane.OK_CANCEL_OPTION);

                    if (result == JOptionPane.OK_OPTION) {
                        String updatedFlightId = flightIdField.getText();
                        String updatedGuideId = guideIdField.getText();
                        String updatedCompanyId = companyIdField.getText();
                        String updatedPrice = priceField.getText();
                        String updatedFlightInfo = flightInfoField.getText();

                        // TODO: Perform the update operation
                        // Execute the necessary SQL UPDATE command with the updated values
                        try {
                            Flight flight = new Flight(
                              Integer.parseInt(updatedFlightId),Integer.parseInt(updatedGuideId),
                              Integer.parseInt(updatedCompanyId),Integer.parseInt(updatedPrice),
                              updatedFlightInfo
                            );
                            String query = flight.getUpdateQuery(flight,Integer.parseInt(updatedFlightId));
                            System.out.println(query);

                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update successful");
                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Update error");
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Update error "+ex.getMessage());

                        }
                    }
                }
            });

            // Delete button action listener
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRowIndex = flightTable.getSelectedRow();

                    if (selectedRowIndex == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a row to delete.", "Error",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                    int confirmDialogResult = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete this flight?", "Confirm Delete",
                            JOptionPane.YES_NO_OPTION);

                    if (confirmDialogResult == JOptionPane.YES_OPTION) {
                        String flightId = tableModel.getValueAt(selectedRowIndex, 0).toString();

                        // TODO: Perform the delete operation
                        // Execute the necessary SQL DELETE command with the specified flight ID
                        Flight flight = new Flight();
                        String query = flight.getDeleteQuery(Integer.parseInt(flightId));
                        try {
                            if(st.executeUpdate(query)!=0) {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete successful");

                            }
                            else {
                                JOptionPane.showMessageDialog(CompanyView.this,"Delete error");

                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(CompanyView.this,"Delete error "+ex.getMessage());

                        }
                    }
                }
            });

            // Create a panel to hold the flight table
            JPanel flightPanel = new JPanel(new BorderLayout());
            flightPanel.add(new JScrollPane(flightTable), BorderLayout.CENTER);

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel();
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold both the flight table and the buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(flightPanel, BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the flight table and buttons in a dialog
            JOptionPane.showMessageDialog(this, contentPanel, "Flight Entries",
                    JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewBus() {
        String companyID = JOptionPane.showInputDialog(this, "Enter company_id:", "View Bus",
                JOptionPane.QUESTION_MESSAGE);

        try {
            // Construct the query to retrieve buses for the specified company
            String query = "SELECT * FROM bus WHERE company_id = " + companyID;
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the bus data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the bus table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add bus rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the bus table model
            JTable busTable = new JTable(tableModel);

            // Insert button action listener
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Bus ID:"));
                    JTextField busIdField = new JTextField();
                    inputPanel.add(busIdField);
                    inputPanel.add(new JLabel("Guide ID:"));
                    JTextField guideIdField = new JTextField();
                    inputPanel.add(guideIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyID);
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Price:"));
                    JTextField priceField = new JTextField();
                    inputPanel.add(priceField);
                    inputPanel.add(new JLabel("Trip Info:"));
                    JTextField tripInfoField = new JTextField();
                    inputPanel.add(tripInfoField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Bus",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String busId = busIdField.getText();
                        String guideId = guideIdField.getText();
                        String companyId = companyIdField.getText();
                        String price = priceField.getText();
                        String tripInfo = tripInfoField.getText();
                        // Perform the necessary SQL insert operation

                        Bus bus = new Bus(
                          Integer.parseInt(busId),Integer.parseInt(guideId),
                          Integer.parseInt(companyId),
                          Integer.parseInt(price),tripInfo
                        );

                        String insertQuery = bus.getInsertQuery(bus);
                        System.out.println(insertQuery);
                        int insertResult = 0;
                        try {
                            insertResult = st.executeUpdate(insertQuery);
                            if (insertResult > 0) {
                                JOptionPane.showMessageDialog(null, "Bus inserted successfully.", "Insert Bus",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to insert bus.", "Insert Bus",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to insert bus. "+ex.getMessage(), "Insert Bus",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Update button action listener
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRow = busTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a bus to update.", "Update Bus",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    String busId = busTable.getValueAt(selectedRow, 0).toString();
                    String guideId = busTable.getValueAt(selectedRow, 1).toString();
                    String companyId = busTable.getValueAt(selectedRow, 2).toString();
                    String price = busTable.getValueAt(selectedRow, 3).toString();
                    String tripInfo = busTable.getValueAt(selectedRow, 4).toString();

                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Bus ID:"));
                    JTextField busIdField = new JTextField(busId);
                    busIdField.setEditable(false);
                    inputPanel.add(busIdField);
                    inputPanel.add(new JLabel("Guide ID:"));
                    JTextField guideIdField = new JTextField(guideId);
                    inputPanel.add(guideIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    JTextField companyIdField = new JTextField(companyId);
                    companyIdField.setEditable(false);
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Price:"));
                    JTextField priceField = new JTextField(price);
                    inputPanel.add(priceField);
                    inputPanel.add(new JLabel("Trip Info:"));
                    JTextField tripInfoField = new JTextField(tripInfo);
                    inputPanel.add(tripInfoField);

                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Bus",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String newGuideId = guideIdField.getText();
                        String newPrice = priceField.getText();
                        String newTripInfo = tripInfoField.getText();

                        // Perform the necessary SQL update operation
                        Bus bus = new Bus(
                                Integer.parseInt(busId),Integer.parseInt(newGuideId),
                                Integer.parseInt(companyID),
                                Integer.parseInt(newPrice), newTripInfo
                        );
                        String updateQuery = bus.getUpdateQuery(bus,Integer.parseInt(busId));
                        System.out.println(updateQuery);
                        int updateResult = 0;
                        try {
                            updateResult = st.executeUpdate(updateQuery);
                            if (updateResult > 0) {
                                JOptionPane.showMessageDialog(null, "Bus updated successfully.", "Update Bus",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to update bus.", "Update Bus",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(null, "Failed to update bus. "+ex.getMessage(), "Update Bus",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Delete button action listener
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRow = busTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a bus to delete.", "Delete Bus",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    String busId = busTable.getValueAt(selectedRow, 0).toString();

                    int confirm = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete the selected bus?", "Delete Bus",
                            JOptionPane.YES_NO_OPTION);
                    if (confirm == JOptionPane.YES_OPTION) {
                        // Perform the necessary SQL delete operation
                        String deleteQuery = new Bus().getDeleteQuery(Integer.parseInt(busId));
                        System.out.println(deleteQuery);
                        int deleteResult = 0;
                        try {
                            deleteResult = st.executeUpdate(deleteQuery);
                            if (deleteResult > 0) {
                                JOptionPane.showMessageDialog(null, "Bus deleted successfully.", "Delete Bus",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to delete bus.", "Delete Bus",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to delete bus. "+ex.getMessage(), "Delete Bus",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create a panel to hold the bus table
            JPanel busPanel = new JPanel(new BorderLayout());
            busPanel.add(new JScrollPane(busTable), BorderLayout.CENTER);

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new FlowLayout());
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold the bus table and buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(busPanel, BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the bus table and buttons in a dialog
            JOptionPane.showMessageDialog(this, contentPanel, "Bus Entries", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewTransport() {
        try {
            // Get the company ID from the user
            String companyId = JOptionPane.showInputDialog(this, "Enter company ID:", "View Transport",
                    JOptionPane.QUESTION_MESSAGE);

            // Query the transport table to retrieve the transport entries for the specified company ID
            String query = "SELECT * FROM transport WHERE company_id = '" + companyId + "'";
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the transport data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the transport table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add transport rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the transport table model
            JTable transportTable = new JTable(tableModel);

            // Create a panel to hold the transport table
            JPanel transportPanel = new JPanel(new BorderLayout());
            transportPanel.add(new JScrollPane(transportTable), BorderLayout.CENTER);

            // Create the insert button
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Create input fields for transport details
                    JTextField transportIdField = new JTextField();
                    JTextField respectiveIdField = new JTextField();
                    JTextField personIdField = new JTextField();
                    JTextField transportTypeField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(5, 2));
                    inputPanel.add(new JLabel("Transport ID:"));
                    inputPanel.add(transportIdField);
                    inputPanel.add(new JLabel("Respective ID:"));
                    inputPanel.add(respectiveIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Transport Type:"));
                    inputPanel.add(transportTypeField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Transport",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String transportId = transportIdField.getText();
                        String respectiveId = respectiveIdField.getText();
                        String personId = personIdField.getText();
                        String transportType = transportTypeField.getText();

                        // Perform the necessary SQL insert operation
                        // TODO
                        Transport transport = new Transport(
                          Integer.parseInt(transportId),Integer.parseInt(companyId),
                          Integer.parseInt(respectiveId),Integer.parseInt(personId),
                                transportType
                        );


                        String insertQuery = transport.getInsertQuery(transport);
                        int insertResult = 0;
                        try {
                            insertResult = st.executeUpdate(insertQuery);
                            if (insertResult > 0) {
                                JOptionPane.showMessageDialog(null, "Transport inserted successfully.", "Insert Transport",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to insert transport.", "Insert Transport",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to insert transport. "+ex.getMessage(), "Insert Transport",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create the update button
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRow = transportTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a transport to update.", "Update Transport",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    String transportId = transportTable.getValueAt(selectedRow, 0).toString();

                    // Create input fields for transport details
                    JTextField respectiveIdField = new JTextField();
                    JTextField personIdField = new JTextField();
                    JTextField transportTypeField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(4, 2));
                    inputPanel.add(new JLabel("Respective ID:"));
                    inputPanel.add(respectiveIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Transport Type:"));
                    inputPanel.add(transportTypeField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Transport",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String respectiveId = respectiveIdField.getText();
                        String personId = personIdField.getText();
                        String transportType = transportTypeField.getText();

                        Transport transport = new Transport(
                                Integer.parseInt(transportId),Integer.parseInt(companyId),
                                Integer.parseInt(respectiveId),Integer.parseInt(personId),
                                transportType
                        );

                        // Perform the necessary SQL update operation
                        String updateQuery = transport.getUpdateQuery(transport,Integer.parseInt(transportId));
                        int updateResult = 0;
                        try {
                            updateResult = st.executeUpdate(updateQuery);
                            if (updateResult > 0) {
                                JOptionPane.showMessageDialog(null, "Transport updated successfully.", "Update Transport",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to update transport.", "Update Transport",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to update transport. "+ex.getMessage(), "Update Transport",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create the delete button
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRow = transportTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a transport to delete.", "Delete Transport",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    String transportId = transportTable.getValueAt(selectedRow, 0).toString();

                    int confirm = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete the selected transport?", "Delete Transport",
                            JOptionPane.YES_NO_OPTION);
                    if (confirm == JOptionPane.YES_OPTION) {
                        // Perform the necessary SQL delete operation
                        Transport transport = new Transport();
                        String deleteQuery = transport.getDeleteQuery(Integer.parseInt(transportId));
                        int deleteResult = 0;
                        try {
                            deleteResult = st.executeUpdate(deleteQuery);
                            if (deleteResult > 0) {
                                JOptionPane.showMessageDialog(null, "Transport deleted successfully.", "Delete Transport",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to delete transport.", "Delete Transport",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to delete transport. "+ex.getMessage(), "Delete Transport",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create a panel to hold the transport table
            JPanel transportPanel2 = new JPanel(new BorderLayout());
            transportPanel2.add(new JScrollPane(transportTable), BorderLayout.CENTER);

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new FlowLayout());
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold the transport table and buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(transportPanel2, BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the transport table and buttons in a dialog
            JOptionPane.showMessageDialog(this, contentPanel, "Transport Entries",
                    JOptionPane.PLAIN_MESSAGE);

        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }



    private void viewCompany() {
        try {
            // Execute the query to fetch company entries
            String query = "SELECT * FROM company";
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the company data
            DefaultTableModel tableModel = new DefaultTableModel();
            tableModel.addColumn("Company ID");
            tableModel.addColumn("Company Name");

            // Add company rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[2];
                row[0] = resultSet.getString("company_id");
                row[1] = resultSet.getString("company_name");
                tableModel.addRow(row);
            }

            // Create a JTable with the company table model
            JTable companyTable = new JTable(tableModel);

            // Create the insert button
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Create input fields for company details
                    JTextField companyIdField = new JTextField();
                    JTextField companyNameField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(2, 2));
                    inputPanel.add(new JLabel("Company ID:"));
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Company Name:"));
                    inputPanel.add(companyNameField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Company",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String companyId = companyIdField.getText();
                        String companyName = companyNameField.getText();

                        // Perform the necessary SQL insert operation
                        String insertQuery = "INSERT INTO company (company_id, company_name) VALUES ('" +
                                companyId + "', '" + companyName + "')";
                        int insertResult = 0;
                        try {
                            insertResult = st.executeUpdate(insertQuery);
                            if (insertResult > 0) {
                                JOptionPane.showMessageDialog(null, "Company inserted successfully.", "Insert Company",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to insert company.", "Insert Company",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to insert company. "+ex.getMessage(), "Insert Company",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create the update button
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRow = companyTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a company to update.", "Update Company",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    String companyId = companyTable.getValueAt(selectedRow, 0).toString();

                    // Create input fields for company details
                    JTextField companyNameField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(2, 2));
                    inputPanel.add(new JLabel("Company ID:"));
                    inputPanel.add(new JLabel(companyId));
                    inputPanel.add(new JLabel("Company Name:"));
                    inputPanel.add(companyNameField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Company",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String companyName = companyNameField.getText();

                        // Perform the necessary SQL update operation
                        String updateQuery = "UPDATE company SET company_name = '" + companyName +
                                "' WHERE company_id = '" + companyId + "'";
                        int updateResult = 0;
                        try {
                            updateResult = st.executeUpdate(updateQuery);
                            if (updateResult > 0) {
                                JOptionPane.showMessageDialog(null, "Company updated successfully.", "Update Company",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to update company.", "Update Company",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to update company. "+ex.getMessage(), "Update Company",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create the delete button
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    int selectedRow = companyTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a company to delete.", "Delete Company",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    String companyId = companyTable.getValueAt(selectedRow, 0).toString();

                    // Confirm the deletion with the user
                    int confirmResult = JOptionPane.showConfirmDialog(null,
                            "Are you sure you want to delete the selected company?", "Delete Company",
                            JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
                    if (confirmResult == JOptionPane.YES_OPTION) {
                        // Perform the necessary SQL delete operation
                        String deleteQuery = "DELETE FROM company WHERE company_id = '" + companyId + "'";
                        int deleteResult = 0;
                        try {
                            deleteResult = st.executeUpdate(deleteQuery);
                            if (deleteResult > 0) {
                                JOptionPane.showMessageDialog(null, "Company deleted successfully.", "Delete Company",
                                        JOptionPane.INFORMATION_MESSAGE);
                            }
                            else {
                                JOptionPane.showMessageDialog(null, "Failed to delete company.", "Delete Company",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to delete company. "+ex.getMessage(), "Delete Company",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel();
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold the company table and buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(new JScrollPane(companyTable), BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Display the company table and buttons in a dialog
            JOptionPane.showMessageDialog(null, contentPanel, "Company Entries",
                    JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void viewTour() {
        try {
            // Prompt the user to enter the company ID
            String companyID = JOptionPane.showInputDialog(this, "Enter company ID:", "View Tours",
                    JOptionPane.QUESTION_MESSAGE);

            // Execute the query to fetch tour entries for the specified company ID
            String query = "SELECT * FROM tour WHERE company_id = " + companyID;
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the tour data
            DefaultTableModel tableModel = new DefaultTableModel();
            tableModel.addColumn("Tour ID");
            tableModel.addColumn("Person ID");
            tableModel.addColumn("Company ID");
            tableModel.addColumn("Accommodation ID");
            tableModel.addColumn("Transport ID");
            tableModel.addColumn("Total Price");

            // Add tour rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[6];
                row[0] = resultSet.getString("tour_id");
                row[1] = resultSet.getString("person_id");
                row[2] = resultSet.getString("company_id");
                row[3] = resultSet.getString("acc_id");
                row[4] = resultSet.getString("transport_id");
                row[5] = resultSet.getString("tot_price");
                tableModel.addRow(row);
            }

            // Create a JTable with the tour table model
            JTable tourTable = new JTable(tableModel);

            // Create the insert button
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Create input fields for tour details
                    JTextField tourIdField = new JTextField();
                    JTextField personIdField = new JTextField();
                    JTextField companyIdField = new JTextField(companyID);
                    JTextField accIdField = new JTextField();
                    JTextField transportIdField = new JTextField();
                    JTextField totalPriceField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(6, 2));
                    inputPanel.add(new JLabel("Tour ID:"));
                    inputPanel.add(tourIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Accommodation ID:"));
                    inputPanel.add(accIdField);
                    inputPanel.add(new JLabel("Transport ID:"));
                    inputPanel.add(transportIdField);
                    inputPanel.add(new JLabel("Total Price:"));
                    inputPanel.add(totalPriceField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Tour",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String tourId = tourIdField.getText();
                        String personId = personIdField.getText();
                        String companyId = companyIdField.getText();
                        String accId = accIdField.getText();
                        String transportId = transportIdField.getText();
                        String totalPrice = totalPriceField.getText();

                        //TODO calculate total price

                        // Perform the necessary SQL insert operation
                        String insertQuery = "INSERT INTO tour (tour_id, person_id, company_id, acc_id, transport_id, tot_price) VALUES ('" +
                                tourId + "', '" + personId + "', '" + companyId + "', '" + accId + "', '" + transportId + "', '" + totalPrice + "')";
                        System.out.println(insertQuery);

                        int insertResult = 0;
                        try {

                            insertResult = st.executeUpdate(insertQuery);
                            if (insertResult > 0) {
                                JOptionPane.showMessageDialog(CompanyView.this, "Tour inserted successfully.");
                            }
                            else {

                                JOptionPane.showMessageDialog(CompanyView.this, "Failed to insert tour.");
                            }

                        } catch (SQLException ex) {
                            JOptionPane.showMessageDialog(CompanyView.this, "Failed to insert tour. :"+ex.getMessage());
                            ex.printStackTrace();
                        }
                    }
                }
            });

            // Create the update button
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row from the tour table
                    int selectedRow = tourTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a tour to update.", "Update Tour",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    // Get the existing data from the selected row
                    String tourId = tourTable.getValueAt(selectedRow, 0).toString();
                    String personId = tourTable.getValueAt(selectedRow, 1).toString();
                    String companyId = tourTable.getValueAt(selectedRow, 2).toString();
                    String accId = tourTable.getValueAt(selectedRow, 3).toString();
                    String transportId = tourTable.getValueAt(selectedRow, 4).toString();
                    String totalPrice = tourTable.getValueAt(selectedRow, 5).toString();

                    // Create input fields and populate them with the existing data
                    JTextField tourIdField = new JTextField(tourId);
                    JTextField personIdField = new JTextField(personId);
                    JTextField companyIdField = new JTextField(companyId);
                    JTextField accIdField = new JTextField(accId);
                    JTextField transportIdField = new JTextField(transportId);
                    JTextField totalPriceField = new JTextField(totalPrice);

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(6, 2));
                    inputPanel.add(new JLabel("Tour ID:"));
                    inputPanel.add(tourIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Accommodation ID:"));
                    inputPanel.add(accIdField);
                    inputPanel.add(new JLabel("Transport ID:"));
                    inputPanel.add(transportIdField);
                    inputPanel.add(new JLabel("Total Price:"));
                    inputPanel.add(totalPriceField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Tour",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String newTourId = tourIdField.getText();
                        String newPersonId = personIdField.getText();
                        String newCompanyId = companyIdField.getText();
                        String newAccId = accIdField.getText();
                        String newTransportId = transportIdField.getText();
                        String newTotalPrice = totalPriceField.getText();

                        // Perform the necessary SQL update operation
                        String updateQuery = "UPDATE tour SET tour_id = '" + newTourId + "', person_id = '" + newPersonId +
                                "', company_id = '" + newCompanyId + "', acc_id = '" + newAccId + "', transport_id = '" +
                                newTransportId + "', tot_price = '" + newTotalPrice + "' WHERE tour_id = '" + tourId + "'";
                        System.out.println(updateQuery);


                        int updateResult = 0;
                        try {
                            updateResult = st.executeUpdate(updateQuery);
                            if (updateResult > 0) {
                                JOptionPane.showMessageDialog(null, "Tour updated successfully.", "Update Tour",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to update tour.", "Update Tour",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        }
                        catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to update tour. "+ex.getMessage(), "Update Tour",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create the delete button
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row from the tour table
                    int selectedRow = tourTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a tour to delete.", "Delete Tour",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    // Confirm the deletion with the user
                    int confirmResult = JOptionPane.showConfirmDialog(null, "Are you sure you want to delete this tour?",
                            "Delete Tour", JOptionPane.YES_NO_OPTION);
                    if (confirmResult == JOptionPane.YES_OPTION) {
                        // Get the tour ID from the selected row
                        String tourId = tourTable.getValueAt(selectedRow, 0).toString();

                        // Perform the necessary SQL delete operation
                        String deleteQuery = "DELETE FROM tour WHERE tour_id = '" + tourId + "'";
                        System.out.println(deleteQuery);
                        int deleteResult = 0;
                        try {
                            deleteResult = st.executeUpdate(deleteQuery);
                            if (deleteResult > 0) {
                                JOptionPane.showMessageDialog(null, "Tour deleted successfully.", "Delete Tour",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to delete tour.", "Delete Tour",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to delete tour. "+ex.getMessage(), "Delete Tour",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel();
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);



            // Create a panel to hold the company table and buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(new JScrollPane(tourTable), BorderLayout.CENTER);
            contentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Show the panel to the user
            JOptionPane.showMessageDialog(this, contentPanel, "View Tours", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void viewGuide() {
        // Ask the user to enter the company ID
        String companyId = JOptionPane.showInputDialog(this, "Enter company ID:", "View Guides",
                JOptionPane.QUESTION_MESSAGE);

        try {
            // Execute the query to retrieve the guides for the specified company ID
            String query = "SELECT * FROM guide WHERE company_id = '" + companyId + "'";
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the guide data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the guide table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add guide rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the guide table model
            JTable guideTable = new JTable(tableModel);

            // Create a panel to hold the guide table
            JPanel guidePanel = new JPanel(new BorderLayout());
            guidePanel.add(new JScrollPane(guideTable), BorderLayout.CENTER);

            // Create the insert button
            JButton insertButton = new JButton("Insert");
            insertButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Create input fields for guide data
                    JTextField guideIdField = new JTextField();
                    JTextField companyIdField = new JTextField();
                    JTextField personIdField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(3, 2));
                    inputPanel.add(new JLabel("Guide ID:"));
                    inputPanel.add(guideIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Insert Guide",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String guideId = guideIdField.getText();
                        String companyId = companyIdField.getText();
                        String personId = personIdField.getText();

                        // Perform the necessary SQL insert operation
                        Guide guide = new Guide(
                          Integer.parseInt(guideId),
                          Integer.parseInt(companyId),
                          Integer.parseInt(personId)
                        );
                        String insertQuery = guide.getInsertQuery(guide);

                        int insertResult = 0;
                        try {

                            insertResult = st.executeUpdate(insertQuery);

                            if (insertResult > 0) {
                                JOptionPane.showMessageDialog(null, "Guide inserted successfully.", "Insert Guide",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to insert guide.", "Insert Guide",
                                        JOptionPane.ERROR_MESSAGE);

                            }

                        } catch (SQLException ex) {

                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to insert guide. "+ex.getMessage(), "Insert Guide",
                                    JOptionPane.ERROR_MESSAGE);
                        }
                    }
                }
            });

            // Create the update button
            JButton updateButton = new JButton("Update");
            updateButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row from the guide table
                    int selectedRow = guideTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a guide to update.", "Update Guide",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    // Get the existing data from the selected row
                    String guideId = guideTable.getValueAt(selectedRow, 0).toString();
                    String companyId = guideTable.getValueAt(selectedRow, 1).toString();
                    String personId = guideTable.getValueAt(selectedRow, 2).toString();

                    // Create input fields for updated guide data
                    JTextField guideIdField = new JTextField(guideId);
                    JTextField companyIdField = new JTextField(companyId);
                    JTextField personIdField = new JTextField(personId);

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(3, 2));
                    inputPanel.add(new JLabel("Guide ID:"));
                    inputPanel.add(guideIdField);
                    inputPanel.add(new JLabel("Company ID:"));
                    inputPanel.add(companyIdField);
                    inputPanel.add(new JLabel("Person ID:"));
                    inputPanel.add(personIdField);

                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Update Guide",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String updatedGuideId = guideIdField.getText();
                        String updatedCompanyId = companyIdField.getText();
                        String updatedPersonId = personIdField.getText();

                        // Perform the necessary SQL update operation
                        Guide guide = new Guide(
                                Integer.parseInt(updatedGuideId),
                                Integer.parseInt(updatedCompanyId),
                                Integer.parseInt(updatedPersonId)
                        );

                        String updateQuery = guide.getUpdateQuery(guide,Integer.parseInt(guideId));


                        int updateResult = 0;
                        try {
                            updateResult = st.executeUpdate(updateQuery);
                            if (updateResult > 0) {
                                JOptionPane.showMessageDialog(null, "Guide updated successfully.", "Update Guide",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to update guide.", "Update Guide",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to update guide. "+ex.getMessage(), "Update Guide",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });

            // Create the delete button
            JButton deleteButton = new JButton("Delete");
            deleteButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Get the selected row from the guide table
                    int selectedRow = guideTable.getSelectedRow();
                    if (selectedRow == -1) {
                        JOptionPane.showMessageDialog(null, "Please select a guide to delete.", "Delete Guide",
                                JOptionPane.WARNING_MESSAGE);
                        return;
                    }

                    // Confirm the deletion with the user
                    int confirmResult = JOptionPane.showConfirmDialog(null, "Are you sure you want to delete this guide?",
                            "Delete Guide", JOptionPane.YES_NO_OPTION);
                    if (confirmResult == JOptionPane.YES_OPTION) {
                        // Get the guide ID from the selected row
                        String guideId = guideTable.getValueAt(selectedRow, 0).toString();

                        // Perform the necessary SQL delete operation
                        String deleteQuery = new Guide().getDeleteQuery(Integer.parseInt(guideId));
                        int deleteResult = 0;
                        try {
                            deleteResult = st.executeUpdate(deleteQuery);
                            if (deleteResult > 0) {
                                JOptionPane.showMessageDialog(null, "Guide deleted successfully.", "Delete Guide",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to delete guide.", "Delete Guide",
                                        JOptionPane.ERROR_MESSAGE);
                            }
                        } catch (SQLException ex) {
                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to delete guide. "+ex.getMessage(), "Delete Guide",
                                    JOptionPane.ERROR_MESSAGE);
                        }


                    }
                }
            });


            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new FlowLayout());
            buttonPanel.add(insertButton);
            buttonPanel.add(updateButton);
            buttonPanel.add(deleteButton);

            // Create a panel to hold the guide table and buttons
            JPanel guideContentPanel = new JPanel(new BorderLayout());
            guideContentPanel.add(new JScrollPane(guideTable), BorderLayout.CENTER);
            guideContentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Show the panel to the user
            JOptionPane.showMessageDialog(this, guideContentPanel, "View Guides", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }


    private void transferGuide() {
        // Ask the user to enter the company ID
        String companyId = JOptionPane.showInputDialog(this, "Enter company ID:", "Transfer Guides",
                JOptionPane.QUESTION_MESSAGE);

        try {
            // Execute the query to retrieve the guides for the specified company ID
            String query = "SELECT * FROM guide WHERE company_id = '" + companyId + "'";
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the guide data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the guide table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add guide rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the guide table model
            JTable guideTable = new JTable(tableModel);

            // Create a panel to hold the guide table
            JPanel guidePanel = new JPanel(new BorderLayout());
            guidePanel.add(new JScrollPane(guideTable), BorderLayout.CENTER);

            // Create the insert button
            JButton transferButton = new JButton("Transfer");
            transferButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Create input fields for guide data
                    JTextField guideIdField = new JTextField();
                    JTextField companyIdField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(2, 2));
                    inputPanel.add(new JLabel("Guide ID:"));
                    inputPanel.add(guideIdField);
                    inputPanel.add(new JLabel("New Company ID:"));
                    inputPanel.add(companyIdField);


                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Transfer Guide",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String guideId = guideIdField.getText();
                        String companyId = companyIdField.getText();

                        //CALL transfer_guide(guideID,newCompanyID);
                        String insertQuery = "CALL transfer_guide("+guideId+", "+companyId+")";

                        int insertResult = 0;
                        try {

                            insertResult = st.executeUpdate(insertQuery);

                            if (insertResult == 0) {
                                JOptionPane.showMessageDialog(null, "Guide transferred successfully.", "Transfer Guide",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to transfer guide.", "Transfer Guide",
                                        JOptionPane.ERROR_MESSAGE);

                            }

                        } catch (SQLException ex) {

                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to transfer guide. "+ex.getMessage(), "Transfer Guide",
                                    JOptionPane.ERROR_MESSAGE);
                        }
                    }
                }
            });


            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new FlowLayout());
            buttonPanel.add(transferButton);


            // Create a panel to hold the guide table and buttons
            JPanel guideContentPanel = new JPanel(new BorderLayout());
            guideContentPanel.add(new JScrollPane(guideTable), BorderLayout.CENTER);
            guideContentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Show the panel to the user
            JOptionPane.showMessageDialog(this, guideContentPanel, "Transfer Guides", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    private void transferCarRental() {
        // Ask the user to enter the company ID
        String personId = JOptionPane.showInputDialog(this, "Enter personID:", "Tranfer Car Rental",
                JOptionPane.QUESTION_MESSAGE);

        try {
            // Execute the query to retrieve the guides for the specified company ID
            String query = "SELECT * FROM car_rental WHERE person_id = '" + personId + "'";
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the guide data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the guide table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add guide rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the guide table model
            JTable guideTable = new JTable(tableModel);

            // Create a panel to hold the guide table
            JPanel guidePanel = new JPanel(new BorderLayout());
            guidePanel.add(new JScrollPane(guideTable), BorderLayout.CENTER);

            // Create the insert button
            JButton transferButton = new JButton("Transfer");
            transferButton.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    // Create input fields for guide data
                    JTextField oldIdField = new JTextField();
                    JTextField newIdField = new JTextField();

                    // Create a panel to hold the input fields
                    JPanel inputPanel = new JPanel(new GridLayout(2, 2));
                    inputPanel.add(new JLabel("Old Person ID:"));
                    inputPanel.add(oldIdField);
                    inputPanel.add(new JLabel("New Person ID:"));
                    inputPanel.add(newIdField);


                    // Show the input panel to the user
                    int result = JOptionPane.showConfirmDialog(null, inputPanel, "Transfer Car Rental",
                            JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
                    if (result == JOptionPane.OK_OPTION) {
                        String oldId = oldIdField.getText();
                        String newId = newIdField.getText();

                        //CALL transfer_guide(guideID,newCompanyID);
                        String insertQuery = "CALL transfer_car_rental("+oldId+", "+newId+")";

                        int insertResult = 0;
                        try {

                            insertResult = st.executeUpdate(insertQuery);

                            if (insertResult == 0) {
                                JOptionPane.showMessageDialog(null, "Car Rental transferred successfully.", "Transfer Car Rental",
                                        JOptionPane.INFORMATION_MESSAGE);
                            } else {
                                JOptionPane.showMessageDialog(null, "Failed to transfer Car Rental.", "Transfer Car Rental",
                                        JOptionPane.ERROR_MESSAGE);

                            }

                        } catch (SQLException ex) {

                            ex.printStackTrace();
                            JOptionPane.showMessageDialog(null, "Failed to transfer Car Rental. "+ex.getMessage(), "Transfer Car Rental",
                                    JOptionPane.ERROR_MESSAGE);
                        }
                    }
                }
            });


            // Create a panel to hold the buttons
            JPanel buttonPanel = new JPanel(new FlowLayout());
            buttonPanel.add(transferButton);


            // Create a panel to hold the guide table and buttons
            JPanel guideContentPanel = new JPanel(new BorderLayout());
            guideContentPanel.add(new JScrollPane(guideTable), BorderLayout.CENTER);
            guideContentPanel.add(buttonPanel, BorderLayout.SOUTH);

            // Show the panel to the user
            JOptionPane.showMessageDialog(this, guideContentPanel, "Transfer Car Rental", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
