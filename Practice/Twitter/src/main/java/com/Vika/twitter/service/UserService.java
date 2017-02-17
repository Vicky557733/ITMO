package com.Vika.twitter.service;

import com.Vika.twitter.models.User;

import java.util.List;

public interface UserService {
    void save(User user);
    User addUser(User user);
    void deleteUserById(Long id);
    User getUserById(Long id);
    User editUser(User user);
    long getCountUsers();
    Iterable<User> getAllUsers();
    User findUserByUsername(String username);
    List<User> findAllUsersByName(String name);
    List<User> findAllUsersBySurname(String surname);


}
