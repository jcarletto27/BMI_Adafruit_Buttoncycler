document.addEventListener('DOMContentLoaded', function () {
	document.forms['settings'].addEventListener('submit', function (e) {
		e.preventDefault();
		onSubmit(this);			
		
	});
});


		function onSubmit(form){
			
			if (document.getElementById("bmi_host_password").value.length > 7				 || document.getElementById("credentials").classList.contains("hidden")) {
				submitAnimation();

				// Make a new timeout set to go off in 1000ms (1 second)
				setTimeout(function () {
					// submit form after timeout
					form.submit();
				}, 100);			
			} else {
				alert("You are required to provide a password of 8 characters or more");
			}
		}

function submitAnimation() {
	$('#topDiv').animate({
		//51% for chrome				
		height: "51%"
		, opacity: 1
	}, 300);
	$('#bottomDiv').animate({
		//51% for chrome
		height: "51%"
		, opacity: 1
	}, 300, function () {
		$('#centerDiv').css({ display: "block" }).animate({
			width: "0%",
			left: "50%"
		}, 300);
	}
	);
}

function setAnim(e) {
	document.getElementById("submitButton").classList.add("hidden");
	document.getElementById("submitButton").offsetHeight;

	var btn = document.getElementsByTagName("button");
	for (i = 0; i < btn.length; i++) {
		btn[i].classList.remove("clicked");
	}
	var formSegs = document.getElementsByClassName("formSeg");
	for (x = 0; x < formSegs.length; x++) {
		formSegs[x].classList.add("hidden");
	}

	setDisabled(document, true);

	e.classList.toggle("clicked");
	switch (e.id.toString()) {
		case "btn-0":
			credentialSetMode();
			break;
		case "btn-1":
			modeSetMode();
			break;
		case "btn-2":
			pixelSetMode();
			break;
	}
}

function setDisabled(parentElement, disable) {
	var inputList = parentElement.querySelectorAll("input, select");
	for (var input in inputList) {
		var el = inputList[input];
		el.disabled = disable;
	}
}



function credentialSetMode() {
	var formElement = document.getElementById("credentials");
	formElement.classList.remove("hidden");
	showSubmit();
	setDisabled(formElement, false);
}

function modeSetMode() {
	var formElement = document.getElementById("modes");
	formElement.classList.remove("hidden");
	showSubmit();
	setDisabled(formElement, false);
}

function pixelSetMode() {
	var formElement = document.getElementById("pixels");
	formElement.classList.remove("hidden");
	showSubmit();
	setDisabled(formElement, false);
}

function showSubmit() {
	var formElement = document.getElementById("submitButton");
	formElement.classList.remove("submit_animate");
	formElement.classList.add("submit_animate");
	formElement.classList.remove("hidden");
}