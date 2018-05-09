<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<div class="container-wrapper">
	<div class="container">
		<h2>All Users</h2>
		<p>고객 명단</p>
		<table class="table table-striped">
			<thead>
				<tr class="bg-warning">
					<th>아이디</th>
					<th>날짜</th>
					<th>시간</th>
					<th>화장실 이용 횟수</th>
					<th>낙상 사고</th>
					<th>위급 상황</th>
					<th>외부 침입</th>
				</tr>
			</thead>
			<tbody>
				<c:forEach var="emer" items="${emergency}">
					<!-- items값과  Contoller의 키값과 일치해야함 -->
					<tr>
						<td>${emer.emergency_id}</td>
						<td>${emer.date}</td>
						<td>${emer.time}</td>
						<td>${emer.count_toilet}</td>
						<td>${emer.count_slip}</td>
						<td>${emer.sos}</td>
						<td>${emer.theft}</td>
					</tr>
				</c:forEach>
			</tbody>
		</table>
	</div>
</div>