package com.Vika.twitter.models.repositories;

import com.Vika.twitter.models.User;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

public interface UserRepository extends CrudRepository<User, Long> {
    @Query("select u from User u where u.id = :id")
    User findUserById(@Param("id") Long id);

    @Query("select u from User u where u.name = ?1")
    List<User> findAllByName(String name);

    @Query("select u from User u where u.surname = ?1")
    List<User> findAllBySurname(String surname);

    @Query("select u from User u where u.username = ?1")
    List<User> findAllByUsername(String username);
}
