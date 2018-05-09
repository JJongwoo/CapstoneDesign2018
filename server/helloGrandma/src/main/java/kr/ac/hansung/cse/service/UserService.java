package kr.ac.hansung.cse.service;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import kr.ac.hansung.cse.dao.UserDao;
import kr.ac.hansung.cse.model.Emergency;
import kr.ac.hansung.cse.model.User;

@Service
public class UserService {

	@Autowired
	private UserDao userDao;
	
	public List<User> getUsers(){
		return userDao.getUsers();
	}

	
	
}
