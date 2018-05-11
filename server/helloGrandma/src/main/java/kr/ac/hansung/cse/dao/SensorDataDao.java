package kr.ac.hansung.cse.dao;


import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import javax.sql.DataSource;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import kr.ac.hansung.cse.model.Status;
import kr.ac.hansung.cse.service.SensorDataService;

@Repository
public class SensorDataDao {

	private JdbcTemplate jdbcTemplate;

	@Autowired
	public void setDataSource(DataSource dataSource) {
		 jdbcTemplate = new JdbcTemplate(dataSource); 
	}

	public void saveData(String pir1, String pir2, String datetime, String id, String sona1, String sona2, String btn, String location, String shock) {

		String sqlStatement = "insert into sensors (sensor_id, datetime, pir_living, pir_bath, sona_living, sona_bath, sos, location, shock)" 
												+ "values(?, ?, ?, ?, ?, ?, ?, ?, ?)";

		System.out.println(id + " " + datetime +  " " + pir1 + " " + pir2 + " " + sona1 + " " + sona2 + " " + btn + " " + location + " " + shock);
		
		boolean a = (jdbcTemplate.update(sqlStatement, new Object[] { id, datetime, pir1, pir2, sona1, sona2, btn, location, shock}) == 1);
	}
	
	public List<Status> getStatus(int i) {
		
		String sqlStatement = "select * from sensors order by datetime desc limit " + i;
		
		
		return jdbcTemplate.query(sqlStatement, new RowMapper<Status>(){
			
			@Override public Status mapRow(ResultSet rs, int arg1) throws SQLException {
				  Status status = new Status(); 
				  status.setSensor_id(rs.getString("sensor_id"));
				  status.setPir_living(rs.getString("pir_living"));
				  status.setPir_bath(rs.getString("pir_bath"));
				  status.setSona_living(rs.getString("sona_living"));
				  status.setSona_bath(rs.getString("sona_bath"));
				  status.setSos(rs.getString("sos"));
				  status.setDatetime(rs.getString("datetime"));
				  status.setLocation(rs.getString("location"));
				  status.setShock(rs.getString("shock"));
				  
				  return status;
			}// query sql record->object
			
		});
		
	}

}
