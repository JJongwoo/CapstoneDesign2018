package kr.ac.hansung.cse.dao;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import javax.sql.DataSource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import kr.ac.hansung.cse.model.Emergency;
import kr.ac.hansung.cse.model.User;

@Repository
public class UserDao {

	private JdbcTemplate jdbcTemplate;

	@Autowired
	public void setDataSource(DataSource dataSource) {// dao-context.xml에 bean에대한 정보(BasicDataSource)
		jdbcTemplate = new JdbcTemplate(dataSource);
	}
	
	public List<User> getUsers(){
		
		String sqlStatement = "select * from users"; // record -> object  :  maprow가 하는일 레코드를 객체로 매핑
		
		return jdbcTemplate.query(sqlStatement,  new RowMapper<User>() {

			@Override
			public User mapRow(ResultSet rs, int rowNum) throws SQLException {
				
				User user = new User();
				user.setUsername(rs.getString("username"));
				user.setPassword(rs.getString("password"));
				user.setEnabled(rs.getInt("enabled"));
				user.setName(rs.getString("name"));
				user.setPhone(rs.getString("phone"));
				user.setAddress(rs.getString("address"));
				
				return user;
			}
			
			
		});
		
	}
	
}