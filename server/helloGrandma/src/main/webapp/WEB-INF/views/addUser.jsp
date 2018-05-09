<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib uri="http://www.springframework.org/tags/form" prefix="sf"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>

<div class="container-wrapper">
	<div class="container">
		<h1>Add User</h1>
		<p class="lead">아래 내용을 작성해주세요 . / Fill the below information to add a User:</p>
		
		
		<sf:form action="${pageContext.request.contextPath}/admin/userManager/addUser"
			method="post" modelAttribute="user">
			
			<!-- path값은 실제product객체의 변수이름과 같아야한다. -->
			<div class="form-group">
				<label for="name">Name</label>
				<sf:input path="name" id="name" class="form=control"/>
			</div>
			
			<div class="form-group">
				<label for="id">Id</label>
				<sf:input path="id" id="id" class="form-control"/>
			</div>	
			
			<div class="form-group">
				<label for="phone">Phone</label>
				<sf:input path="phone" id="phone" class="form-control"/>
				
			</div>
			
			<div class="form-group">
				<label for="address">Address</label>
				<sf:input path="address" id="address" class="form-control"/>
				
			</div>
			
			<input type="submit" value="submit" class="btn btn-default">
			<a href="<c:url value="/admin/userManager"/>" class="btn btn-default">취소</a>
		</sf:form>
		<br/>
	</div>
</div>