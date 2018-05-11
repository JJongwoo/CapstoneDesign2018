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

@Repository
public class EmergencyDao {

	private JdbcTemplate jdbcTemplate;

	@Autowired
	public void setDataSource(DataSource dataSource) {
		 jdbcTemplate = new JdbcTemplate(dataSource); 
	}
	
	public void addEmergency(Emergency emergency) {
		
		String emergency_id = emergency.getEmergency_id();
		String datetime  = emergency.getDatetime();
		int count_toilet = emergency.getCount_toilet();
		int count_slip = emergency.getCount_slip();
		int sos = emergency.getSos();
		int theft = emergency.getTheft();
		
		String sqlStatement = "insert into emergency (emergency_id, datetime, count_toilet, count_slip, sos, theft) "
								+ "values(?, ?, ?, ?, ?, ?)";
		System.out.println(emergency);
		
		boolean a = jdbcTemplate.update(sqlStatement, new Object[] {emergency_id, datetime, count_toilet
				, count_slip, sos, theft})==1;
	}
	
	public List<Emergency> viewEmergency(String id) {
		
		String sqlStatement = "select * from emergency where emergency_id = ?" ;
		return jdbcTemplate.query(sqlStatement,  new Object[] {id},
				new RowMapper<Emergency>() {

					@Override
					public Emergency mapRow(ResultSet rs, int arg1) throws SQLException {
						Emergency emergency = new Emergency();
						emergency.setEmergency_id(rs.getString("emergency_id"));
						emergency.setDatetime(rs.getString("datetime"));
						emergency.setCount_slip(rs.getInt("count_slip"));
						emergency.setCount_toilet(rs.getInt("count_toilet"));
						emergency.setSos(rs.getInt("sos"));
						emergency.setTheft(rs.getInt("theft"));
						return emergency;
					}
		});
	}
	
	public List<Emergency> getEmergency(int count){
		
		String sqlStatement = "select * from emergency where count_toilet=1 order by datetime desc limit ?" ;
		
		return jdbcTemplate.query(sqlStatement,  new Object[] {count},
				new RowMapper<Emergency>() {

					@Override
					public Emergency mapRow(ResultSet rs, int arg1) throws SQLException {
						Emergency emergency = new Emergency();
						emergency.setEmergency_id(rs.getString("emergency_id"));
						emergency.setDatetime(rs.getString("datetime"));
						emergency.setCount_slip(rs.getInt("count_slip"));
						emergency.setCount_toilet(rs.getInt("count_toilet"));
						emergency.setSos(rs.getInt("sos"));
						emergency.setTheft(rs.getInt("theft"));
						return emergency;
					}
		});
	}

	public int getEmergencyByStatus(String status) {
			
		String sqlStatement = "select count(*) from emergency where ? = 1" ;
		
		int count = jdbcTemplate.queryForObject(sqlStatement, new Object[] {status}, Integer.class);
		
		return count;
	}

}
