package com.Vika.twitter.models.repositories;

import com.Vika.twitter.models.Note;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import java.util.Date;

public interface NoteRepository extends CrudRepository<Note, Long> {
    @Query("select b from Note b where b.user = :id")
    Iterable<Note> findAllByUserId(@Param("id") Long id);

    @Query("select b from Note b where b.creationDate = :date")
    Iterable<Note> findAllByDate(@Param("date") Date date);
}
