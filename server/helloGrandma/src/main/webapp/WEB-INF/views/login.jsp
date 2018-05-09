<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">


<div>
	<div class="container">

		<c:if test="${not empty errorMsg}">
			<div style="color: #ff0000;">
				<h3>${errorMsg}</h3>
			</div>
		</c:if>
		
		<c:if test="${not empty logoutMsg}">
			<div style="color: #00ffff;">
				<h3>${logoutMsg}</h3>
			</div>
		</c:if>
		
		<form action="<c:url value="/login"/>" method="post"
			class="form-signin">
			<img class="mb-4"
				src="<c:url value="resources/image/helloGrandMa.png"/>" alt=""
				style="width: 85%; height: 85%">
			<div class="form-group">
				<label for="username">아이디 : </label> <input type="text"
					class="form-control" id="username" placeholder="아이디를 입력하세요"
					name="username" style="width: 90%">
				<%--이 name은 중요 form의 username이란 이름으로 넘어감 --%>
			</div>
			<div class="form-group">
				<label for="pwd">비밀번호 : </label> <input type="password"
					class="form-control" id="pwd" placeholder="비밀번호를 입력하세요"
					name="password" style="width: 90%">
			</div>

			<input type="hidden" name="${_csrf.parameterName }"
				value="${_csrf.token }" />

			<button type="submit" class="btn btn-primary">로그인</button>
		</form>
	</div>
</div>