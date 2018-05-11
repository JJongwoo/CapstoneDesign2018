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
import kr.ac.hansung.cse.model.Status;

@Repository
public class EmergencyDao {

	private JdbcTemplate jdbcTemplate;

	@Autowired
	public void setDataSource(DataSource dataSource) {
		jdbcTemplate = new JdbcTemplate(dataSource);
	}

	public void addEmergency(Emergency emergency) {

		String emergency_id = emergency.getEmergency_id();
		String time = emergency.getTime();
		String date = emergency.getDate();
		int count_toilet = emergency.getCount_toilet();
		int count_slip = emergency.getCount_slip();
		int sos = emergency.getSos();
		int theft = emergency.getTheft();

		String sqlStatement = "insert into emergency (emergency_id, time, date, count_toilet, count_slip, sos, theft) "
				+ "values(?, ?, ?, ?, ?, ?, ?)";
		System.out.println(emergency);

		boolean a = jdbcTemplate.update(sqlStatement,
				new Object[] { emergency_id, time, date, count_toilet, count_slip, sos, theft }) == 1;
	}

	public List<Emergency> viewEmergency(String id) {

		String sqlStatement = "select * from emergency where emergency_id = ?";
		System.out.println(id);
		return jdbcTemplate.query(sqlStatement, new Object[] { id }, new RowMapper<Emergency>() {

			@Override
			public Emergency mapRow(ResultSet rs, int arg1) throws SQLException {
				Emergency emergency = new Emergency();
				emergency.setEmergency_id(rs.getString("emergency_id"));
				emergency.setDate(rs.getString("date"));
				emergency.setTime(rs.getString("time"));
				emergency.setCount_slip(rs.getInt("count_slip"));
				emergency.setCount_toilet(rs.getInt("count_toilet"));
				emergency.setSos(rs.getInt("sos"));
				emergency.setTheft(rs.getInt("theft"));
				return emergency;
			}
		});
	}

	// 2분 내에 3번이상.

	public int getBathCount(String id) {
		String sqlStatement = "select count(*) from emergency where emergency_id = ? AND count_toilet = 1";
		System.out.println(id);
		return jdbcTemplate.queryForObject(sqlStatement, new Object[] { id }, Integer.class);
	}

	public List<Emergency> getEmergency(int count) {
		String sqlStatement = "select * from sensors where date ='2018-05-08' order by time desc limit " + i;

		return jdbcTemplate.query(sqlStatement, new RowMapper<Status>() {
			dateTime.split(" ");
			
			@Override
			public Status mapRow(ResultSet rs, int arg1) throws SQLException {
				Status status = new Status();
				status.setSensor_id(rs.getString("sensor_id"));
				status.setPir_living(rs.getString("pir_living"));
				status.setPir_bath(rs.getString("pir_bath"));
				status.setSona_living(rs.getString("sona_living"));
				status.setSona_bath(rs.getString("sona_bath"));
				status.setSos(rs.getString("sos"));
				status.setTime(rs.getString("time"));
				status.setDate(rs.getString("date"));
				status.setLocation(rs.getString("location"));

				return status;
			}// query sql record->object

		});
	}

}
