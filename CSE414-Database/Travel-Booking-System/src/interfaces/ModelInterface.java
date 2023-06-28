package interfaces;

import java.sql.ResultSet;
import java.sql.SQLException;

public interface ModelInterface<T> {
    public T exportTableInstance(ResultSet rs) throws SQLException;
    public String getSelectQuery(int id);
    public String getSelectAllQuery();
    public String getDeleteQuery(int id);
    public String getDeleteAllQuery();
    public String getInsertQuery(T object);
    public String getUpdateQuery(T object,int id);
}
