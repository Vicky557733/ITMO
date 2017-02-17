package com.Vika.twitter.config;

import com.Vika.twitter.utils.MySQLUserDetailsService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;

@Configuration
@EnableWebSecurity

public class WebSecurityConfig extends WebSecurityConfigurerAdapter {

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http
                .authorizeRequests()
                    .antMatchers("/css/**","/js/**","/fonts/**","/images/**", "/", "/home", "/registration","/login").permitAll()
                    .anyRequest().access("hasAnyRole('ROLE_ADMIN', 'ROLE_USER')")
                .and()
                    .formLogin()
                    .loginPage("/login")
                    .usernameParameter("login_username")
                    .passwordParameter("login_password")
                    .defaultSuccessUrl("/logged_user", true)
                    .permitAll()
                .and()
                    .logout()
                    .permitAll();
    }

    @Autowired
    private MySQLUserDetailsService mySQLUserDetailsService;

    @Autowired
    public void configureGlobal(AuthenticationManagerBuilder auth) throws Exception {
        auth.userDetailsService(mySQLUserDetailsService);
    }
}