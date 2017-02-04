package com.Vika.twitter;

import com.Vika.twitter.models.Note;
import com.Vika.twitter.models.User;
import com.Vika.twitter.models.repositories.NoteRepository;
import com.Vika.twitter.models.repositories.UserRepository;
import com.Vika.twitter.service.impl.NoteServiceImpl;
import com.Vika.twitter.service.impl.UserServiceImpl;
import org.slf4j.Logger;

import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.support.ClassPathXmlApplicationContext;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

@SpringBootApplication
public class Application {
    // JDBC variables for opening and managing connection
    private static Connection con;
    private static Statement stmt;
    private static ResultSet rs;

    private static final Logger log = LoggerFactory.getLogger(Application.class);

    public static void main(String[] args) {
        SpringApplication.run(Application.class);
    }

    @Bean
    public CommandLineRunner demo(UserServiceImpl userServiceImpl) {
        return (args) -> {
            User user = new User("Victoria", "Abcd", "qwe", "17ewq");

            System.out.println("User with id = 5 : " + userServiceImpl.getUserById(5L).toString());


            for (User findUser : userServiceImpl.getAllUsers()) {
                System.out.println(findUser.toString());
            }

            String query = "select count(*) from note";

            try {
                // opening database connection to MySQL server
                con = DriverManager.getConnection("jdbc:mysql://localhost:3306/testdb", "root", "12345");

                // getting Statement object to execute query
                stmt = con.createStatement();

                // executing SELECT query
                rs = stmt.executeQuery(query);

                while (rs.next()) {
                    int count = rs.getInt(1);
                    System.out.println("Total number of note in the table : " + count);
                }

            } catch (SQLException sqlEx) {
                sqlEx.printStackTrace();
            } finally {
                //close connection ,stmt and resultset here
                try { con.close(); } catch(SQLException se) { /*can't do anything */ }
                try { stmt.close(); } catch(SQLException se) { /*can't do anything */ }
                try { rs.close(); } catch(SQLException se) { /*can't do anything */ }
            }
        };
    }
}

