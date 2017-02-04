package com.Vika.twitter.models.repositories;

import com.Vika.twitter.models.User;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

public interface UserRepository extends CrudRepository<User, Long> {
    @Query("select b from User b where b.id = :id")
    User findUserById(@Param("id") Long id);
}
