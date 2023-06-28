package models;

import javax.swing.table.DefaultTableModel;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

public class TableModel {
    public static DefaultTableModel buildTableModel(ResultSet resultSet) throws SQLException {
        ResultSetMetaData metaData = resultSet.getMetaData();

        // Get column names
        int columnCount = metaData.getColumnCount();
        String[] columnNames = new String[columnCount];
        for (int column = 1; column <= columnCount; column++) {
            columnNames[column - 1] = metaData.getColumnName(column);
        }

        // Get row data
        java.util.List<Object[]> data = new java.util.ArrayList<>();
        while (resultSet.next()) {
            Object[] rowData = new Object[columnCount];
            for (int column = 1; column <= columnCount; column++) {
                rowData[column - 1] = resultSet.getObject(column);
            }
            data.add(rowData);
        }

        // Create and return table model
        return new DefaultTableModel(data.toArray(new Object[0][]), columnNames);
    }
}
