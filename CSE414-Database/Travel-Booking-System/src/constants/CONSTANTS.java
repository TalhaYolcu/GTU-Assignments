package constants;
public class CONSTANTS {
    public static final String MYSQL_CLASS_NAME = "com.mysql.cj.jdbc.Driver";
    public static String MYSQL_URL = "jdbc:mysql://localhost:3306/travel_booking";
    public static String MYSQL_USERNAME = "root";
    public static String MYSQL_PASSWORD = "root";
    public static String DB_NAME = "travel_booking";

    public static class TABLE_NAMES {
        public static String accommodation = "accommodation";
        public static String bus = "bus";
        public static String car = "car";
        public static String car_rental = "car_rental";
        public static String company = "company";
        public static String flight = "flight";
        public static String guide = "guide";
        public static String hotel = "hotel";
        public static String person = "person";
        public static String room = "room";
        public static String tour = "tour";
        public static String transport = "transport";
    }

    public static class ACCOMMODATION_TABLE {
        public static String acc_id = "acc_id";
        public static String company_id = "company_id";
        public static String hotel_id = "hotel_id";
        public static String room_id = "room_id";
        public static String person_id = "person_id";
        public static String check_in_date = "check_in_date";
        public static String check_out_date = "check_out_date";
        public static int column_count = 7;
        public static String[] column_names = new String[]{acc_id, company_id, hotel_id, room_id, person_id, check_in_date, check_out_date};
    }

    public static class BUS_TABLE {
        public static String bus_id = "bus_id";
        public static String guide_id = "guide_id";
        public static String company_id = "company_id";
        public static String price = "price";
        public static String trip_info = "trip_info";
        public static int column_count = 5;
        public static String[] column_names = new String[]{bus_id, guide_id, company_id, price, trip_info};
    }

    public static class CAR_TABLE {
        public static String car_id = "car_id";
        public static String company_id = "company_id";
        public static String car_properties = "car_properties";
        public static String daily_price = "daily_price";
        public static int column_count = 4;
        public static String[] column_names = new String[]{car_id, company_id, car_properties, daily_price};
    }

    public static class CAR_RENTAL_TABLE {
        public static String rental_id = "rental_id";
        public static String car_id = "car_id";
        public static String person_id = "person_id";
        public static String start_date = "start_date";
        public static String end_date = "end_date";
        public static String company_id = "company_id";
        public static int column_count = 6;
        public static String[] column_names = new String[]{rental_id, car_id, person_id, start_date, end_date, company_id};
    }

    public static class COMPANY_TABLE {
        public static String company_id = "company_id";
        public static String company_name = "company_name";
        public static int column_count = 2;
        public static String[] column_names = new String[]{company_id, company_name};
    }

    public static class FLIGHT_TABLE {
        public static String flight_id = "flight_id";
        public static String guide_id = "guide_id";
        public static String company_id = "company_id";
        public static String flight_info = "flight_info";
        public static String price = "price";
        public static int column_count = 5;
        public static String[] column_names = new String[]{flight_id, guide_id, company_id, flight_info, price};
    }

    public static class GUIDE_TABLE {
        public static String guide_id = "guide_id";
        public static String company_id = "company_id";
        public static String person_id = "person_id";
        public static int column_count = 3;
        public static String[] column_names = new String[]{guide_id, company_id, person_id};
    }

    public static class HOTEL_TABLE {
        public static String hotel_id = "hotel_id";
        public static String hotel_name = "hotel_name";
        public static String company_id = "company_id";
        public static int column_count = 3;
        public static String[] column_names = new String[]{hotel_id, hotel_name, company_id};
    }

    public static class PERSON_TABLE {
        public static String person_id = "person_id";
        public static String name = "name";
        public static String birthdate = "birthdate";
        public static String budget = "budget";
        public static int column_count = 4;
        public static String[] column_names = new String[]{person_id, name, birthdate, budget};
    }

    public static class ROOM_TABLE {
        public static String room_id = "room_id";
        public static String hotel_id = "hotel_id";
        public static String daily_price = "daily_price";
        public static String room_properties = "room_properties";
        public static int column_count = 4;
        public static String[] column_names = new String[]{room_id, hotel_id, daily_price, room_properties};
    }

    public static class TOUR_TABLE {
        public static String tour_id = "tour_id";
        public static String person_id = "person_id";
        public static String company_id = "company_id";
        public static String acc_id = "acc_id";
        public static String transport_id = "transport_id";
        public static String tot_price = "tot_price";
        public static int column_count = 6;
        public static String[] column_names = new String[]{tour_id, person_id, company_id, acc_id, transport_id, tot_price};
    }

    public static class TRANSPORT_TABLE {
        public static String transport_id = "transport_id";
        public static String company_id = "company_id";
        public static String respective_id = "respective_id";
        public static String person_id = "person_id";
        public static String transport_type = "transport_type";
        public static int column_count = 5;
        public static String[] column_names = new String[]{transport_id, company_id, respective_id, person_id, transport_type};
    }
}
