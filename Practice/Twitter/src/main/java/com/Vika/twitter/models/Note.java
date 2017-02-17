package com.Vika.twitter.models;

import org.hibernate.annotations.GenericGenerator;

import javax.persistence.*;
import java.util.Date;


@Entity
@Table(name = "notes")
public class Note {
    @Id
    @GeneratedValue(generator = "increment")
    @GenericGenerator(name= "increment", strategy= "increment")
    @Column(name = "id", nullable = false)
    private Long id;

    @ManyToOne
    @JoinColumn(name = "user_id", nullable = false)
    private User user;

    @Column(name = "body")
    private String body;

    @Column(name = "creation_date")
    @Temporal(value=TemporalType.TIMESTAMP)
    private Date creationDate;

    protected Note() {}

    public Note(User user, String body) {
        this.user = user;
        this.body = body;
        this.creationDate = new Date();
    }

    public Long getId() {
        return id;
    }

    public User getUser() {
        return user;
    }

    public String getBody() {
        return body;
    }

    public Date getCreationDate() {
        return creationDate;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public void setBody(String body) {
        this.body = body;
    }

    public void setCreationDate(Date creationDate) {
        this.creationDate = creationDate;
    }

    @Override
    public String toString() {
        return "Note{" +
                "id=" + id +
                ", userId=" + user.getId() +
                ", body='" + body + '\'' +
                ", creationDate=" + creationDate +
                '}';
    }
}

