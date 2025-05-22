/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   START_MENU.js                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

var START_MENU_IS_ACTIVE = false;
var SRV_STATUS_DOM = undefined;

function
	START_CLICKED()
{
	const START = document.getElementById("START");
	const START_MENU = document.getElementById("START_MENU");

	START_MENU_IS_ACTIVE = true;
	START.classList.add("ACTIVE");
	START_MENU.style.display = "FLEX";
}

function
	CLOSE_START_MENU()
{
	if (START_MENU_IS_ACTIVE)
	{
		const START = document.getElementById("START");
		const START_MENU = document.getElementById("START_MENU");

		if (!START || !START_MENU)
			return ;

		START.classList.remove("ACTIVE");
		START_MENU.style.display = "NONE";
		START_MENU_IS_ACTIVE = false;
	}
}

async function
	START_LOGOUT()
{
	SRV_STATUS_DOM = undefined;
	CLOSE_START_MENU()

	if (TIME_INTERVAL !== undefined)
		clearInterval(TIME_INTERVAL);

	Object.entries(OS.PROCESS).forEach(
		function ([PID, APP])
		{
			CLOSE_WINDOW(PID);
		}
	);
	DESKTOP.APPS.innerHTML = "";
	DESKTOP.THIS.classList.remove("ACTIVE");

	if (document.getElementById("START_BAR"))
		document.getElementById("START_BAR").remove();

	await AJAX_SEND("/ajax/usermanagement/logout/", {});
	RUN_APP("LOGIN");
}

function
	START_SETTINGS()
{
	RUN_APP("SETTINGS");
}

function
	SRV_STATUS(STATUS)
{
	// DEAD
	// GET
	// SEND
	// SOCKET
	// ONLINE

	if (typeof(SRV_STATUS_DOM) !== "undefined" && SRV_STATUS_DOM !== null)
	{
		SRV_STATUS_DOM.src = "/IMAGES/START/SRV_" + STATUS + ".png";
	}
	else
		SRV_STATUS_DOM = document.getElementById("SRV_STATUS");
}

async function
	CHECK_SERVER_STATUS(DELAY = 1000)
{
	while (SRV_STATUS_DOM !== undefined)
	{
		const SUCCESS = await AJAX_GET("/ajax/usermanagement/server_health");

		if (SUCCESS)
			SRV_STATUS("ONLINE");
		else
			SRV_STATUS("DEAD");

		await new Promise((RESOLVE) => setTimeout(RESOLVE, DELAY));
	}
}
