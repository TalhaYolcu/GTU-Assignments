package gui;
import db.TravelBookingConnection;
import models.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;

public class GuideView extends JFrame {
    private JButton viewToursButton;
    private JButton viewRentingsButton;
    private JButton rentCarButton;
    private JButton cancelCarRentingButton;
    private JButton viewHotelsButton;
    private JButton viewHotelRoomsButton;
    private JButton accommodateButton;
    private JButton cancelAccommodationButton;
    private JButton viewFlightsButton;
    private JButton buyFlightButton;
    private JButton cancelFlightButton;
    private JButton viewBusesButton;
    private JButton buyBusButton;
    private JButton cancelBusButton;
    private JButton cancelTourJoiningButton;
    private JButton viewGuidedTransportsButton;
    private JButton viewAllPossibilitiesButton;
    private JButton addBudgetButton;
    private JButton removeBudgetButton;
    private JButton viewAllTransportationButton;
    private Statement st ;


    public GuideView() {
        initializeComponents();
        setupLayout();
        setupListeners();
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setTitle("Guide View");
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
        viewRentingsButton = new JButton("View Rentings");
        rentCarButton = new JButton("Rent a Car");
        cancelCarRentingButton = new JButton("Cancel Car Renting");
        viewHotelsButton = new JButton("View Hotels");
        viewHotelRoomsButton = new JButton("View Hotel Rooms");
        viewAllPossibilitiesButton = new JButton("View All Possibilites");
        accommodateButton = new JButton("Accommodate");
        cancelAccommodationButton = new JButton("Cancel Accommodation");
        viewFlightsButton = new JButton("View Flights");
        buyFlightButton = new JButton("Buy a Flight");
        cancelFlightButton = new JButton("Cancel a Flight");
        viewBusesButton = new JButton("View Buses");
        buyBusButton = new JButton("Buy a Bus");
        cancelBusButton = new JButton("Cancel a Bus");
        viewToursButton = new JButton("View Tours");
        cancelTourJoiningButton = new JButton("Cancel Tour Joining");
        viewGuidedTransportsButton = new JButton("View Guided Transports");
        addBudgetButton=new JButton("Add Budget");
        removeBudgetButton = new JButton("Remove Budget");
        viewAllTransportationButton = new JButton("View all Transportation");
    }

    private void setupLayout() {
        setLayout(new GridLayout(7, 3));
        //TODO copy person
        add(viewRentingsButton);
        add(rentCarButton);
        add(cancelCarRentingButton);
        add(viewFlightsButton);
        add(buyFlightButton);
        add(cancelFlightButton);
        add(viewBusesButton);
        add(buyBusButton);
        add(cancelBusButton);
        add(viewHotelsButton);
        add(viewHotelRoomsButton);
        add(viewAllPossibilitiesButton);
        add(accommodateButton);
        add(cancelAccommodationButton);
        add(viewToursButton);
        add(cancelTourJoiningButton);
        add(viewGuidedTransportsButton);
        add(addBudgetButton);
        add(removeBudgetButton);
        add(viewAllTransportationButton);
    }

    private void setupListeners() {
        viewToursButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewTours();
            }
        });

        viewRentingsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewRentings();
            }
        });

        rentCarButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                rentCar();
            }
        });

        cancelCarRentingButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cancelCarRenting();
            }
        });

        viewHotelsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewHotels();
            }
        });

        viewHotelRoomsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewHotelRooms();
            }
        });

        accommodateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                accommodate();
            }
        });

        cancelAccommodationButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cancelAccommodation();
            }
        });

        viewFlightsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewFlights();
            }
        });

        buyFlightButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buyFlight();
            }
        });

        cancelFlightButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cancelFlight();
            }
        });

        viewBusesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewBuses();
            }
        });

        buyBusButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buyBus();
            }
        });

        cancelBusButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cancelBus();
            }
        });
        viewGuidedTransportsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewGuidedTransports();
            }
        });
        viewAllPossibilitiesButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewAllPossibilities();
            }
        });
        cancelTourJoiningButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                cancelTourJoining();
            }
        });
        addBudgetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addBudget();
            }
        });
        removeBudgetButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                removeBudget();
            }
        });
        viewAllTransportationButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                viewAllTransportation();
            }
        });

    }


    private void viewRentings() {
        try {
            Car carModel = new Car();
            ResultSet resultSet = st.executeQuery(carModel.getSelectAllQuery());
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();

            // Create a table model to hold the data
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the table model
            JTable table = new JTable(tableModel);

            // Display the table in a dialog
            JOptionPane.showMessageDialog(this, new JScrollPane(table), "Rentings", JOptionPane.INFORMATION_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void rentCar() {
        try {
            Car carTemp=new Car();
            ResultSet resultSet = st.executeQuery(carTemp.getSelectAllQuery()) ;
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();

            // Create a table model to hold the data
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the table model
            JTable table = new JTable(tableModel);

            // Create a panel to hold the table and input field
            JPanel panel = new JPanel(new BorderLayout());
            panel.add(new JScrollPane(table), BorderLayout.CENTER);


            // Display the table and input field in a dialog
            int option = JOptionPane.showOptionDialog(
                    this,
                    panel,
                    "Available Rentings",
                    JOptionPane.OK_CANCEL_OPTION,
                    JOptionPane.INFORMATION_MESSAGE,
                    null,
                    new Object[]{"OK", "Cancel"},
                    null
            );
            int selectedRow = table.getSelectedRow();
            // Check if the user clicked OK and a car ID is entered
            if (option == JOptionPane.OK_OPTION && selectedRow!=-1) {

                // Perform necessary SQL operations to update the car_rental table

                int carId = Integer.parseInt(table.getValueAt(selectedRow,0).toString());
                int companyId = Integer.parseInt(table.getValueAt(selectedRow,1).toString());
                String carProperty =table.getValueAt(selectedRow,2).toString();
                int dailyPrice = Integer.parseInt(table.getValueAt(selectedRow,3).toString());


                JPanel datePanel = new JPanel(new GridLayout(3,2));
                datePanel.add(new JLabel("Person ID: "));
                JTextField personIdField=new JTextField();
                datePanel.add(personIdField);
                datePanel.add(new JLabel("Start date: "));
                JTextField startD=new JTextField();
                datePanel.add(startD);
                datePanel.add(new JLabel("End date: "));
                JTextField endD=new JTextField();
                datePanel.add(endD);



                int result = JOptionPane.showConfirmDialog(null, datePanel, "Car",
                        JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

                if(result==JOptionPane.OK_OPTION) {
                    Date startDate = Date.valueOf(startD.getText());
                    Date endDate = Date.valueOf(endD.getText());
                    int personId = Integer.parseInt(personIdField.getText());
                    CarRental carRental = new CarRental(0,carId,personId,startDate,endDate,companyId);



                    String query = carRental.getInsertQuery(carRental);
                    System.out.println(query);
                    try {
                        if(st.executeUpdate(query)!=0) {
                            JOptionPane.showMessageDialog(null, "Car rental successful.");
                        }
                        else {
                            JOptionPane.showMessageDialog(null, "Car rental failed.");

                        }
                    }
                    catch (SQLException ex) {
                        ex.printStackTrace();
                        JOptionPane.showMessageDialog(null, "Car rental failed : "+ex.getMessage());

                    }
                }
            }

        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void cancelCarRenting() {
        try {
            // Prompt the user to enter a person ID
            String personIdString = JOptionPane.showInputDialog(this, "Enter Person ID:");
            if (personIdString == null || personIdString.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Invalid Person ID entered or canceled!");
                return;
            }

            int personId = Integer.parseInt(personIdString);

            // Execute the query to retrieve car rental entries for the person
            String query = "SELECT * FROM car_rental WHERE person_id = " + personId;
            System.out.println(query);

            ResultSet resultSet = st.executeQuery(query);

            // Check if there are any car rental entries for the person
            if (!resultSet.isBeforeFirst()) {
                JOptionPane.showMessageDialog(this, "No car rental entries found for Person ID: " + personId);
                return;
            }

            // Create a table model to hold the data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the table model
            JTable table = new JTable(tableModel);

            // Display the table in a dialog
            int result =  JOptionPane.showConfirmDialog(this, new JScrollPane(table), "Car Rental Entries for Person ID: " + personId, JOptionPane.PLAIN_MESSAGE);


            int selectedRow = table.getSelectedRow();
            if(selectedRow==-1) {
                return;
            }
            String rentalIdString = table.getValueAt(selectedRow,0).toString();

            int rentalId = Integer.parseInt(rentalIdString);

            // Delete the entry from the car_rental table
            String deleteQuery = "DELETE FROM car_rental WHERE rental_id = " + rentalId;
            System.out.println(deleteQuery);

            try {

                int deleteCount = st.executeUpdate(deleteQuery);

                if (deleteCount > 0) {
                    JOptionPane.showMessageDialog(this, "Car rental entry deleted successfully!");

                } else {
                    JOptionPane.showMessageDialog(this, "Failed to delete car rental entry!");

                }
            }
            catch (SQLException ex) {
                ex.printStackTrace();
            }


        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void viewHotels() {
        try {
            // Create a HotelModel instance to interact with the hotel table
            Hotel hotelModel = new Hotel();

            // Execute the query to retrieve all hotels
            ResultSet resultSet = st.executeQuery(hotelModel.getSelectAllQuery());

            // Create a table model to hold the data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add rows to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the table model
            JTable table = new JTable(tableModel);

            // Display the table in a dialog
            JOptionPane.showMessageDialog(this, new JScrollPane(table), "Hotels", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewHotelRooms() {
        try {
            // Create a HotelModel instance to interact with the hotel table
            Hotel hotelModel = new Hotel();

            // Execute the query to retrieve all hotels
            ResultSet resultSet = st.executeQuery(hotelModel.getSelectAllQuery());

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

            // Create a panel to hold the hotel table
            JPanel hotelPanel = new JPanel(new BorderLayout());
            hotelPanel.add(new JScrollPane(hotelTable), BorderLayout.CENTER);

            // Display the hotel table in a dialog
            JOptionPane.showMessageDialog(this, hotelPanel, "Hotels", JOptionPane.PLAIN_MESSAGE);

            // Prompt the user to enter a hotel ID
            String hotelID = JOptionPane.showInputDialog(this, "Enter Hotel ID:", "View Hotel Rooms",
                    JOptionPane.QUESTION_MESSAGE);

            if(hotelID==null || hotelID.length()==0) {
                JOptionPane.showMessageDialog(this, "No hotel entered");
                return;

            }

            // Create a RoomModel instance to interact with the room table
            Room roomModel = new Room();

            // Execute the query to retrieve rooms of the specified hotel ID
            ResultSet roomResultSet = st.executeQuery(roomModel.getRoomsByHotelIDQuery(hotelID));

            // Create a table model to hold the room data
            ResultSetMetaData roomMetaData = roomResultSet.getMetaData();
            int roomColumnCount = roomMetaData.getColumnCount();
            DefaultTableModel roomTableModel = new DefaultTableModel();

            // Add column names to the room table model
            for (int columnIndex = 1; columnIndex <= roomColumnCount; columnIndex++) {
                roomTableModel.addColumn(roomMetaData.getColumnName(columnIndex));
            }

            // Add room rows to the table model
            while (roomResultSet.next()) {
                Object[] row = new Object[roomColumnCount];
                for (int columnIndex = 1; columnIndex <= roomColumnCount; columnIndex++) {
                    row[columnIndex - 1] = roomResultSet.getObject(columnIndex);
                }
                roomTableModel.addRow(row);
            }

            // Create a JTable with the room table model
            JTable roomTable = new JTable(roomTableModel);

            // Create a panel to hold the room table
            JPanel roomPanel = new JPanel(new BorderLayout());
            roomPanel.add(new JScrollPane(roomTable), BorderLayout.CENTER);

            // Display the room table in a dialog
            JOptionPane.showMessageDialog(this, roomPanel, "Hotel Rooms", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewAllPossibilities() {
        try {

            // Prompt the user to enter a hotel ID
            String companyID = JOptionPane.showInputDialog(this, "Enter company ID:", "View all possibilites",
                    JOptionPane.QUESTION_MESSAGE);

            // Create a HotelModel instance to interact with the hotel table
           /*String query = "SELECT *\n" +
                   "FROM company\n" +
                   "FULL OUTER JOIN flight ON company.company_id = flight.company_id\n" +
                   "FULL OUTER JOIN car ON company.company_id = car.company_id\n" +
                   "FULL OUTER JOIN bus ON company.company_id = bus.company_id\n" +
                   "WHERE company.company_id = "+ companyID ;
*/
            //MYSQL does not support FULL OUTER JOIN
            String query = "SELECT *\n" +
                    "FROM company\n" +
                    "LEFT JOIN flight ON company.company_id = flight.company_id\n" +
                    "LEFT JOIN car ON company.company_id = car.company_id\n" +
                    "LEFT JOIN bus ON company.company_id = bus.company_id\n" +
                    "UNION\n" +
                    "SELECT *\n" +
                    "FROM company\n" +
                    "RIGHT JOIN flight ON company.company_id = flight.company_id\n" +
                    "RIGHT JOIN car ON company.company_id = car.company_id\n" +
                    "RIGHT JOIN bus ON company.company_id = bus.company_id\n" +
                    "WHERE company.company_id =" + companyID ;

            // Execute the query to retrieve all hotels
            System.out.println(query);
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

            // Create a panel to hold the hotel table
            JPanel hotelPanel = new JPanel(new BorderLayout());
            hotelPanel.add(new JScrollPane(hotelTable), BorderLayout.CENTER);

            // Display the hotel table in a dialog
            JOptionPane.showMessageDialog(this, hotelPanel, "Hotels And Rooms", JOptionPane.PLAIN_MESSAGE);


        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void accommodate() {
        try {
            // Create a HotelModel instance to interact with the hotel table
            Hotel hotelModel = new Hotel();

            // Execute the query to retrieve all hotels
            ResultSet resultSet = st.executeQuery(hotelModel.getSelectAllQuery());

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

            // Create a panel to hold the hotel table
            JPanel hotelPanel = new JPanel(new BorderLayout());
            hotelPanel.add(new JScrollPane(hotelTable), BorderLayout.CENTER);

            // Display the hotel table in a dialog
            int option =  JOptionPane.showConfirmDialog(this, hotelPanel, "Hotels", JOptionPane.PLAIN_MESSAGE);
            if(option == JOptionPane.OK_OPTION) {

                int selectedRowIndex = hotelTable.getSelectedRow();
                if(selectedRowIndex==-1) {
                    return;
                }
                String hotelID = hotelTable.getValueAt(selectedRowIndex,0).toString();
                String companyId = hotelTable.getValueAt(selectedRowIndex,2).toString();

                // Create a RoomModel instance to interact with the room table
                Room roomModel = new Room();

                // Execute the query to retrieve rooms of the specified hotel ID
                ResultSet roomResultSet = st.executeQuery(roomModel.getRoomsByHotelIDQuery(hotelID));

                // Create a table model to hold the room data
                ResultSetMetaData roomMetaData = roomResultSet.getMetaData();
                int roomColumnCount = roomMetaData.getColumnCount();
                DefaultTableModel roomTableModel = new DefaultTableModel();

                // Add column names to the room table model
                for (int columnIndex = 1; columnIndex <= roomColumnCount; columnIndex++) {
                    roomTableModel.addColumn(roomMetaData.getColumnName(columnIndex));
                }

                // Add room rows to the table model
                while (roomResultSet.next()) {
                    Object[] row = new Object[roomColumnCount];
                    for (int columnIndex = 1; columnIndex <= roomColumnCount; columnIndex++) {
                        row[columnIndex - 1] = roomResultSet.getObject(columnIndex);
                    }
                    roomTableModel.addRow(row);
                }

                // Create a JTable with the room table model
                JTable roomTable = new JTable(roomTableModel);

                // Create a panel to hold the room table
                JPanel roomPanel = new JPanel(new BorderLayout());
                roomPanel.add(new JScrollPane(roomTable), BorderLayout.CENTER);

                // Display the room table in a dialog
                int optionRoom =  JOptionPane.showConfirmDialog(this, roomPanel, "Hotel Rooms", JOptionPane.PLAIN_MESSAGE);

                JPanel personIdPanel = new JPanel(new GridLayout(3,2));
                personIdPanel.add(new JLabel("Person ID: "));
                JTextField personIdField = new JTextField();
                personIdPanel.add(personIdField);
                personIdPanel.add(new JLabel("Check in date: "));
                JTextField checkInField = new JTextField();
                personIdPanel.add(checkInField);
                personIdPanel.add(new JLabel("Check out date: "));
                JTextField checkOutField = new JTextField();
                personIdPanel.add(checkOutField);

                int result = JOptionPane.showConfirmDialog(null, personIdPanel, "Flight",
                        JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

                if(optionRoom==JOptionPane.OK_OPTION && result==JOptionPane.OK_OPTION) {
                    // Prompt the user to enter a room ID to accommodate
                    int selectedRoomRow = roomTable.getSelectedRow();
                    if(selectedRoomRow==-1) {
                        return;
                    }
                    String roomID = roomTable.getValueAt(selectedRoomRow,0).toString();
                    String personId = personIdField.getText();
                    Date checkIn = Date.valueOf(checkInField.getText());
                    Date checkOut = Date.valueOf(checkOutField.getText());

                    // Create an AccommodationModel instance to interact with the accommodation table
                    Accommodation accommodationModel = new Accommodation(0,
                            Integer.parseInt(companyId),Integer.parseInt(hotelID),
                            Integer.parseInt(roomID),Integer.parseInt(personId),
                            checkIn,checkOut
                    );

                    //TODO
                    String insertQuery = accommodationModel.getInsertQuery(accommodationModel);

                    try {
                        int rowsAffected = st.executeUpdate(insertQuery);

                        if (rowsAffected > 0) {
                            JOptionPane.showMessageDialog(this, "Accommodation purchased successfully");
                        } else {
                            JOptionPane.showMessageDialog(this, "Failed to Accommodation purchase", "Error", JOptionPane.ERROR_MESSAGE);
                        }
                    }
                    catch (SQLException ex) {
                        ex.printStackTrace();
                        JOptionPane.showMessageDialog(this, "Failed to Accommodation purchase"+ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);

                    }

                }

            }

        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void cancelAccommodation() {
        try {
            // Prompt the user to enter a person ID
            String personID = JOptionPane.showInputDialog(this, "Enter Person ID:", "Cancel Accommodation",
                    JOptionPane.QUESTION_MESSAGE);

            // Execute the query to retrieve accommodation entries for the specified person ID
            String query = "SELECT * FROM accommodation WHERE person_id = " + personID;
            ResultSet resultSet = st.executeQuery(query);

            // Check if there are any accommodation entries for the specified person ID
            if (!resultSet.isBeforeFirst()) {
                JOptionPane.showMessageDialog(this, "No accommodation entries found for Person ID: " + personID,
                        "Cancel Accommodation", JOptionPane.INFORMATION_MESSAGE);
                return;
            }

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

            // Create a panel to hold the accommodation table
            JPanel accommodationPanel = new JPanel(new BorderLayout());
            accommodationPanel.add(new JScrollPane(accommodationTable), BorderLayout.CENTER);

            // Display the accommodation table in a dialog
            JOptionPane.showMessageDialog(this, accommodationPanel, "Accommodation Entries",
                    JOptionPane.PLAIN_MESSAGE);

            int selectedRow = accommodationTable.getSelectedRow();
            if(selectedRow==-1) {
                return;
            }

            String accommodationID = accommodationTable.getValueAt(selectedRow,0).toString();

            // Execute the SQL command to delete the accommodation entry
            String deleteQuery = "DELETE FROM accommodation WHERE acc_id = " + Integer.parseInt(accommodationID);

            try {
                st.executeUpdate(deleteQuery);

                JOptionPane.showMessageDialog(this, "Accommodation cancellation successful!", "Cancel Accommodation",
                        JOptionPane.INFORMATION_MESSAGE);
            }
            catch (SQLException ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(this, "Accommodation cancellation failed! " + ex.getMessage() , "Cancel Accommodation",
                        JOptionPane.INFORMATION_MESSAGE);
            }


        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void viewFlights() {
        try {
            // Execute the query to retrieve all flights
            Flight flight = new Flight();

            ResultSet resultSet = st.executeQuery(flight.getSelectAllQuery());

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

            // Create a panel to hold the flight table
            JPanel flightPanel = new JPanel(new BorderLayout());
            flightPanel.add(new JScrollPane(flightTable), BorderLayout.CENTER);

            // Display the flight table in a dialog
            JOptionPane.showMessageDialog(this, flightPanel, "Flights", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void buyFlight() {
        try {
            // Execute the query to retrieve all flights
            String query = "SELECT * FROM flight";
            ResultSet resultSet = st.executeQuery(query);

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

            // Create a panel to hold the flight table
            JPanel flightPanel = new JPanel(new BorderLayout());
            flightPanel.add(new JScrollPane(flightTable), BorderLayout.CENTER);

            // Display the flight table in a dialog
            int option = JOptionPane.showConfirmDialog(this, flightPanel, "Flights", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

            // Process the user's selection
            if (option == JOptionPane.OK_OPTION) {
                // Get the selected row index
                int selectedRowIndex = flightTable.getSelectedRow();
                if(selectedRowIndex==-1) {
                    return;
                }

                JPanel personIdPanel = new JPanel(new GridLayout(1,2));
                personIdPanel.add(new JLabel("Person ID: "));
                JTextField personIdField = new JTextField();
                personIdPanel.add(personIdField);

                int result = JOptionPane.showConfirmDialog(null, personIdPanel, "Flight",
                        JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

                if (selectedRowIndex != -1 && result==JOptionPane.OK_OPTION) {
                    // Get the flight_id from the selected row
                    String flightId = flightTable.getValueAt(selectedRowIndex, 0).toString();
                    String companyId = flightTable.getValueAt(selectedRowIndex,2).toString();

                    //TODO
                    // Insert the flight into the transport table
                    Transport transport = new Transport(0,
                            Integer.parseInt(companyId),Integer.parseInt(flightId),
                            Integer.parseInt(personIdField.getText()),"flight"

                    );
                    String insertQuery = transport.getInsertQuery(transport);

                    try {

                        int rowsAffected = st.executeUpdate(insertQuery);

                        if (rowsAffected > 0) {
                            JOptionPane.showMessageDialog(this, "Flight purchased successfully");
                        } else {
                            JOptionPane.showMessageDialog(this, "Failed to purchase flight", "Error", JOptionPane.ERROR_MESSAGE);
                        }
                    }
                    catch (SQLException ex) {
                        ex.printStackTrace();
                        JOptionPane.showMessageDialog(this, "Failed to purchase flight "+ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);

                    }
                }
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }



    private void cancelFlight() {
        try {
            // Prompt the user to enter the person ID
            String personId = JOptionPane.showInputDialog(this, "Enter Person ID:");

            if (personId == null || personId.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Invalid Person ID entered or canceled!");
                return;
            }

            // Execute the query to retrieve the flights for the given person ID
            String query = "SELECT * FROM transport WHERE transport_type = 'flight' AND person_id = " + Integer.parseInt(personId);
            ResultSet resultSet = st.executeQuery(query);

            // Check if there are any flights for the given person ID
            if (!resultSet.isBeforeFirst()) {
                JOptionPane.showMessageDialog(this, "No flights found for the specified person ID", "No Flights", JOptionPane.INFORMATION_MESSAGE);
                return;
            }

            // Create a table model to hold the flight data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the flight table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the flight table model
            JTable flightTable = new JTable(tableModel);

            // Create a panel to hold the flight table
            JPanel flightPanel = new JPanel(new BorderLayout());
            flightPanel.add(new JScrollPane(flightTable), BorderLayout.CENTER);

            // Display the flight table in a dialog
            int option = JOptionPane.showConfirmDialog(this, flightPanel, "Cancel Flight", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

            // Process the user's selection
            if (option == JOptionPane.OK_OPTION) {
                int selectedRow = flightTable.getSelectedRow();
                if(selectedRow==-1) {
                    return;
                }
                // Prompt the user to enter the transport ID
                String transportId = flightTable.getValueAt(selectedRow,0).toString();

                // Delete the flight from the transport table
                String deleteQuery = "DELETE FROM transport WHERE transport_id = " + Integer.parseInt(transportId);
                try {

                    int rowsAffected = st.executeUpdate(deleteQuery);

                    if (rowsAffected > 0) {
                        JOptionPane.showMessageDialog(this, "Flight canceled successfully");
                    } else {
                        JOptionPane.showMessageDialog(this, "Failed to cancel flight", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                }
                catch (SQLException ex) {
                    ex.printStackTrace();
                    JOptionPane.showMessageDialog(this, "Failed to cancel flight "+ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);

                }
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void viewBuses() {
        try {
            // Execute the query to retrieve all buses
            Bus bus = new Bus();
            ResultSet resultSet = st.executeQuery(bus.getSelectAllQuery());


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

            // Create a panel to hold the bus table
            JPanel busPanel = new JPanel(new BorderLayout());
            busPanel.add(new JScrollPane(busTable), BorderLayout.CENTER);

            // Display the bus table in a dialog
            JOptionPane.showMessageDialog(this, busPanel, "Buses", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void buyBus() {
        try {
            // Execute the query to retrieve all buses
            String query = "SELECT * FROM bus";
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

            // Create a panel to hold the bus table
            JPanel busPanel = new JPanel(new BorderLayout());
            busPanel.add(new JScrollPane(busTable), BorderLayout.CENTER);

            // Display the bus table in a dialog and prompt for bus ID
            int selectedOption = JOptionPane.showOptionDialog(this, busPanel, "Buy a Bus",
                    JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE, null, null, null);

            if (selectedOption == JOptionPane.OK_OPTION) {
                // Get the selected row from the bus table

                JPanel personIdPanel = new JPanel(new GridLayout(1,2));
                personIdPanel.add(new JLabel("Person ID"));
                JTextField personIdField = new JTextField();
                personIdPanel.add(personIdField);

                int result = JOptionPane.showConfirmDialog(null, personIdPanel, "Bus",
                        JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);

                int selectedRow = busTable.getSelectedRow();


                if (selectedRow != -1 && result == JOptionPane.OK_OPTION) {
                    // Get the bus ID from the selected row

                    int busId = Integer.parseInt(busTable.getValueAt(selectedRow, 0).toString());
                    int companyId = Integer.parseInt(busTable.getValueAt(selectedRow,1).toString());
                    // TODO
                    // Insert a new entry in the transport table for the purchased bus
                    Transport transport = new Transport(0,
                            companyId,busId,
                            Integer.parseInt(personIdField.getText()),"bus"

                    );
                    String insertQuery = transport.getInsertQuery(transport);


                    try {
                        int rowsAffected = st.executeUpdate(insertQuery);

                        if (rowsAffected > 0) {
                            JOptionPane.showMessageDialog(this, "Bus purchased successfully!");
                        } else {
                            JOptionPane.showMessageDialog(this, "Failed to purchase bus.");
                        }
                    }
                    catch (SQLException ex) {
                        ex.printStackTrace();
                        JOptionPane.showMessageDialog(this, "Failed to purchase bus. "+ex.getMessage());

                    }

                } else {
                    JOptionPane.showMessageDialog(this, "No bus selected.");
                }
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }

    private void cancelBus() {
        try {
            // Prompt the user to enter the person ID
            String personIdString = JOptionPane.showInputDialog(this, "Enter person ID:");
            if (personIdString == null || personIdString.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Invalid person ID.");
                return;
            }

            // Parse the person ID
            int personId;
            try {
                personId = Integer.parseInt(personIdString);
            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this, "Invalid person ID.");
                return;
            }

            // Execute the query to retrieve the buses for the given person ID
            String query = "SELECT * FROM transport WHERE transport_type = 'bus' AND person_id = " + personId;
            ResultSet resultSet = st.executeQuery(query);

            // Check if there are any bus entries for the given person ID
            if (!resultSet.isBeforeFirst()) {
                JOptionPane.showMessageDialog(this, "No bus entries found for person ID: " + personId);
                return;
            }

            // Create a table model to hold the bus entries
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the bus table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add bus entries to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the bus entries table model
            JTable busEntriesTable = new JTable(tableModel);

            // Create a panel to hold the bus entries table
            JPanel busEntriesPanel = new JPanel(new BorderLayout());
            busEntriesPanel.add(new JScrollPane(busEntriesTable), BorderLayout.CENTER);

            // Display the bus entries table in a dialog and prompt for bus ID to cancel
            int selectedOption = JOptionPane.showOptionDialog(this, busEntriesPanel, "Cancel Bus",
                    JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE, null, null, null);

            if (selectedOption == JOptionPane.OK_OPTION) {
                // Get the selected row from the bus entries table
                int selectedRow = busEntriesTable.getSelectedRow();
                if (selectedRow != -1) {
                    // Get the transport ID from the selected row
                    int transportId = (int) busEntriesTable.getValueAt(selectedRow, 0);

                    // Delete the bus entry from the transport table
                    String deleteQuery = "DELETE FROM transport WHERE transport_id = " + transportId;
                    try {
                        int rowsAffected = st.executeUpdate(deleteQuery);

                        if (rowsAffected > 0) {
                            JOptionPane.showMessageDialog(this, "Bus entry canceled successfully!");
                        } else {
                            JOptionPane.showMessageDialog(this, "Failed to cancel bus entry.");
                        }
                    }
                    catch (SQLException ex) {
                        ex.printStackTrace();
                        JOptionPane.showMessageDialog(this, "Failed to cancel bus entry. "+ex.getMessage());

                    }
                } else {
                    JOptionPane.showMessageDialog(this, "No bus entry selected.");
                }
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void viewTours() {
        try {
            // Execute the query to retrieve all tours
            String query = "SELECT * FROM tour";
            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the tour entries
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the tour table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add tour entries to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the tour entries table model
            JTable tourEntriesTable = new JTable(tableModel);

            // Create a panel to hold the tour entries table
            JPanel tourEntriesPanel = new JPanel(new BorderLayout());
            tourEntriesPanel.add(new JScrollPane(tourEntriesTable), BorderLayout.CENTER);

            // Display the tour entries table in a dialog
            JOptionPane.showMessageDialog(this, tourEntriesPanel, "View Tour", JOptionPane.PLAIN_MESSAGE);
        } catch (SQLException ex) {
            ex.printStackTrace();
        }
    }


    private void cancelTourJoining() {
        try {
            // Prompt the user to enter the company ID
            String personID = JOptionPane.showInputDialog(this, "Enter person ID:", "Cancel Tours",
                    JOptionPane.QUESTION_MESSAGE);
            String query = "SELECT * FROM tour WHERE person_id = "+personID;
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

            // Create a panel to hold the company table and buttons
            JPanel contentPanel = new JPanel(new BorderLayout());
            contentPanel.add(new JScrollPane(tourTable), BorderLayout.CENTER);


            int option = JOptionPane.showConfirmDialog(this, contentPanel, "View Tours", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
            if(option==JOptionPane.OK_OPTION) {
                // Get the selected row from the tour table
                int selectedRow = tourTable.getSelectedRow();
                if (selectedRow == -1) {
                    JOptionPane.showMessageDialog(null, "Please select a tour to cancel.", "Cancel Tour",
                            JOptionPane.WARNING_MESSAGE);
                    return;
                }
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
                    }
                    else {
                        JOptionPane.showMessageDialog(null, "Failed to delete tour.", "Delete Tour",
                                JOptionPane.ERROR_MESSAGE);
                    }
                }
                catch (SQLException ex) {
                    ex.printStackTrace();
                    JOptionPane.showMessageDialog(null, "Failed to delete tour. "+ex.getMessage(), "Delete Tour",
                            JOptionPane.ERROR_MESSAGE);
                }

            }
        }
        catch (SQLException ex) {
            ex.printStackTrace();
        }
    }
    private void viewGuidedTransports() {
        try {
            String guideId = JOptionPane.showInputDialog(this, "Enter Guide ID:");
            if (guideId == null || guideId.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Invalid Guide ID entered or canceled!");
                return;
            }

            String query = "SELECT DISTINCT * FROM flight,bus WHERE " +
                    "flight.guide_id = "+guideId + " AND bus.guide_id = "+guideId;
            ResultSet resultSet = st.executeQuery(query);

            // Check if there are any flights for the given person ID
            if (!resultSet.isBeforeFirst()) {
                JOptionPane.showMessageDialog(this, "No flights found for the specified person ID", "No Flights", JOptionPane.INFORMATION_MESSAGE);
                return;
            }
            // Create a table model to hold the flight data
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the flight table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }
            // Create a JTable with the flight table model
            JTable guideTable = new JTable(tableModel);

            // Create a panel to hold the flight table
            JPanel guidePanel = new JPanel(new BorderLayout());
            guidePanel.add(new JScrollPane(guideTable), BorderLayout.CENTER);

            JOptionPane.showConfirmDialog(this, guidePanel, "View guidings", JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);


        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    private void removeBudget() {
        try {
            // Prompt the user to enter the company ID
            String personID = JOptionPane.showInputDialog(this, "Enter person ID:", "Remove Budget",
                    JOptionPane.QUESTION_MESSAGE);

            String query = "SELECT budget FROM person WHERE person_id = "+personID;

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
            JTable budgetTable = new JTable(tableModel);
            int budget = Integer.parseInt(budgetTable.getValueAt(0,0).toString());


            JPanel takeAmountPanel = new JPanel(new GridLayout(2,2));
            takeAmountPanel.add(new JLabel("Your budget is : "));
            takeAmountPanel.add(new JLabel(String.valueOf(budget)));
            takeAmountPanel.add(new JLabel("Enter amount to remove : "));
            JTextField textFieldAddAmount = new JTextField();
            takeAmountPanel.add(textFieldAddAmount);

            int option = JOptionPane.showConfirmDialog(null,takeAmountPanel,"Enter amount",
                    JOptionPane.OK_CANCEL_OPTION);

            if(option==JOptionPane.OK_OPTION) {
                String removeAmountString = textFieldAddAmount.getText();
                int removeAmount = Integer.parseInt(removeAmountString);
                try {
                    st.executeUpdate("CALL para_cek("+personID+", "+removeAmount+");");
                    JOptionPane.showMessageDialog(this,"Money removed successfully");
                }
                catch (SQLException ex) {
                    JOptionPane.showMessageDialog(this,"Money couldn't removed "+ex.getMessage());
                    ex.printStackTrace();
                }
            }
        }
        catch (SQLException exception) {
            exception.printStackTrace();
        }
    }

    private void addBudget() {
        try {
            // Prompt the user to enter the company ID
            String personID = JOptionPane.showInputDialog(this, "Enter person ID:", "Add Budget",
                    JOptionPane.QUESTION_MESSAGE);

            String query = "SELECT budget FROM person WHERE person_id = "+personID;

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
            JTable budgetTable = new JTable(tableModel);
            int budget = Integer.parseInt(budgetTable.getValueAt(0,0).toString());


            JPanel takeAmountPanel = new JPanel(new GridLayout(2,2));
            takeAmountPanel.add(new JLabel("Your budget is : "));
            takeAmountPanel.add(new JLabel(String.valueOf(budget)));
            takeAmountPanel.add(new JLabel("Enter amount to add : "));
            JTextField textFieldAddAmount = new JTextField();
            takeAmountPanel.add(textFieldAddAmount);

            int option = JOptionPane.showConfirmDialog(null,takeAmountPanel,"Enter amount",
                    JOptionPane.OK_CANCEL_OPTION);

            if(option==JOptionPane.OK_OPTION) {
                String addAmountString = textFieldAddAmount.getText();
                int addAmount = Integer.parseInt(addAmountString);
                try {
                    st.executeUpdate("CALL para_transfer("+personID+", "+addAmount+");");
                    JOptionPane.showMessageDialog(this,"Money added successfully");
                }
                catch (SQLException ex) {
                    JOptionPane.showMessageDialog(this,"Money couldn't added "+ex.getMessage());
                    ex.printStackTrace();
                }
            }
        }
        catch (SQLException exception) {
            exception.printStackTrace();
        }
    }

    private void viewAllTransportation() {
        try {
            // Prompt the user to enter the company ID
            String companyID = JOptionPane.showInputDialog(this, "Enter company ID:", "See all transportations",
                    JOptionPane.QUESTION_MESSAGE);

            String query = "SELECT bus.trip_info,flight.flight_info\n" +
                    "FROM bus\n" +
                    "INNER JOIN flight ON bus.company_id = flight.company_id;";


            ResultSet resultSet = st.executeQuery(query);

            // Create a table model to hold the tour entries
            ResultSetMetaData metaData = resultSet.getMetaData();
            int columnCount = metaData.getColumnCount();
            DefaultTableModel tableModel = new DefaultTableModel();

            // Add column names to the tour table model
            for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                tableModel.addColumn(metaData.getColumnName(columnIndex));
            }

            // Add tour entries to the table model
            while (resultSet.next()) {
                Object[] row = new Object[columnCount];
                for (int columnIndex = 1; columnIndex <= columnCount; columnIndex++) {
                    row[columnIndex - 1] = resultSet.getObject(columnIndex);
                }
                tableModel.addRow(row);
            }

            // Create a JTable with the tour entries table model
            JTable tourEntriesTable = new JTable(tableModel);

            // Create a panel to hold the tour entries table
            JPanel tourEntriesPanel = new JPanel(new BorderLayout());
            tourEntriesPanel.add(new JScrollPane(tourEntriesTable), BorderLayout.CENTER);

            // Display the tour entries table in a dialog
            JOptionPane.showMessageDialog(this, tourEntriesPanel, "View Tour", JOptionPane.PLAIN_MESSAGE);
        }
        catch (SQLException ex) {
            ex.printStackTrace();
        }
    }
}
