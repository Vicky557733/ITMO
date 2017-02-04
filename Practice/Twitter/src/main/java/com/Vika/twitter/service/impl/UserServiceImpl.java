package com.Vika.twitter.service.impl;

import com.Vika.twitter.models.User;
import com.Vika.twitter.models.repositories.UserRepository;
import com.Vika.twitter.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class UserServiceImpl implements UserService {
    @Autowired
    private UserRepository userRepository;

    @Override
    public User addUser (User user) {
        return userRepository.save(user);
    }

    @Override
    public void deleteUserById(Long id) {
        userRepository.delete(id);
    }

    @Override
    public User getUserById(Long id) {
        return userRepository.findUserById(id);
    }

    @Override
    public User editUser(User user) {
        return userRepository.save(user);
    }

    @Override
    public long getCountUsers() {
        return userRepository.count();
    }

    public Iterable<User> getAllUsers() {
        return userRepository.findAll();
    }
}
