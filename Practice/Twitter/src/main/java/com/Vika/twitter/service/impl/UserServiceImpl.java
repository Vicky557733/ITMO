package com.Vika.twitter.service.impl;

import com.Vika.twitter.models.Role;
import com.Vika.twitter.models.User;
import com.Vika.twitter.models.repositories.RoleRepository;
import com.Vika.twitter.models.repositories.UserRepository;
import com.Vika.twitter.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Component;

import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Component
public class UserServiceImpl implements UserService {
    @Autowired
    private UserRepository userRepository;

    @Autowired
    private RoleRepository roleRepository;

    @Override
    public void save(User user) {
        Set<Role> roles = new HashSet<>();
        roles.add(roleRepository.findOne(1L));
        user.setRoles(roles);
        userRepository.save(user);
    }

    @Override
    public User addUser (User user) {
        Set<Role> roles = new HashSet<>();
        roles.add(roleRepository.findOne(1L));
        user.setRoles(roles);
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

    public User findUserByUsername(String username) {
        final List<User> users = userRepository.findAllByUsername(username);
        if (users.size() > 0)
            return users.get(0);
        return null;
    }

    @Override
    public List<User> findAllUsersByName(String name) {
        return userRepository.findAllByName(name);
    }

    @Override
    public List<User> findAllUsersBySurname(String surname) {
        return userRepository.findAllBySurname(surname);
    }
}
