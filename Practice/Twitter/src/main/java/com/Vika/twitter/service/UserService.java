package com.Vika.twitter.service;

import com.Vika.twitter.models.User;

public interface UserService {
    User addUser(User user);
    void deleteUserById(Long id);
    User getUserById(Long id);
    User editUser(User user);
    long getCountUsers();
    Iterable<User> getAllUsers();
}
