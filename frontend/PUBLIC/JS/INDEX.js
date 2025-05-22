/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INDEX.js                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ***************************** [v] OBJECT [v] ***************************** */
window.$EVAL = eval; /* TO EVAL FUNCTIONS FROM MODULES GLOBALLY */

const APP_NAMES =
[
	"LOGIN",
	"REGISTER",
	"POPUP",
	"MSN",
	"MESSAGE_BOX",
	"PONG",
	"2FA",
	"SETTINGS"
];

const GAME_STYLE =
{
	"RIGHT_PLAYER_COLOR": "C",
	"LEFT_PLAYER_COLOR": "1",
	"BALL_COLOR": "6",
	"TABLE_COLOR": "A"
};

const COLORS =
{
	"0": 0X000000,
	"1": 0X000080,
	"2": 0X008000,
	"3": 0X008080,
	"4": 0X800000,
	"5": 0X800080,
	"6": 0X808000,
	"7": 0XC0C0C0,
	"8": 0X808080,
	"9": 0X0000FF,
	"A": 0X00FF00,
	"B": 0X01FFFF,
	"C": 0XFE0101,
	"D": 0XFF00FF,
	"E": 0XFFFF00,
	"F": 0XFFFFFF
};
/* ***************************** [^] OBJECT [^] ***************************** */

/* ************************* [v] EVENT LISTENER [v] ************************* */
window.addEventListener("popstate",
	async function (EVENT) // FOR GOING BACK OF THE HISTORY EVENT
	{
		if (EVENT.state && EVENT.state.PAGE === "DESKTOP")
			CLOSE_START_MENU()
	}
);

document.addEventListener("contextmenu",
	function(EVENT)
	{
		if (EVENT.target.id === "DESKTOP_BACK")
		{
			LOG("STOP! Don't right click yet");
			// TODO: RIGHT CLICK MENU
			EVENT.preventDefault();
		}
		// else
			// EVENT.preventDefault();
	}, false
);
/* ************************* [^] EVENT LISTENER [^] ************************* */

async function
	MAIN()
{
	await CHECKOAUTH();

	for (const NAME of APP_NAMES)
	{
		OS.APP[NAME] = {};
		OS.APP[NAME].NAME = NAME;
		OS.APP[NAME].PATH = "/APPS/" + NAME + "/";
		OS.APP[NAME].THIS = await AJAX_GET(
			OS.APP[NAME].PATH + "/INDEX.html"
		);
		OS.APP[NAME].META =
			await AJAX_GET(OS.APP[NAME].PATH + "/META.json");
		OS.APP[NAME].DESKTOP = JSON.parse(
			await AJAX_GET(OS.APP[NAME].PATH + "/DESKTOP.json")
		);

		if (!OS.APP[NAME].THIS)
		{
			BSOD(
				"Error: Failed to get app " + 
				"[" + OS.APP[NAME].PATH + "/INDEX.html]"
			);
			return ;
		}
		else if (!OS.APP[NAME].META)
		{
			BSOD(
				"Error: Failed to get app " + 
				"[" + OS.APP[NAME].PATH + "/META.json]"
			);
			return ;
		}
		else if (!OS.APP[NAME].DESKTOP)
		{
			BSOD(
				"Error: Failed to get app " + 
				"[" + OS.APP[NAME].PATH + "/META.json]"
			);
			return ;
		}
		else
		{
			OS.APP[NAME].THIS =
				OS.APP[NAME].THIS.replace(/<!--[\s\S]*?-->/g, '');
		}
	}

	const RESPONSE =
		await AJAX_SEND("/ajax/usermanagement/accessWithToken/", {});

	if (RESPONSE.STATUS)
	{
		LOG(
			__LANG__[LANG].LOGIN.ERROR.UNDEXPECTED_START.MESSAGE +
				" (" + RESPONSE.STATUS + ")",
			"ERROR",
			{
				TITLE: __LANG__[LANG].LOGIN.ERROR.UNDEXPECTED_START.TITLE,
				BUTTON_DISPLAY: false
			}
		);

		async function
			START_SERVER_WHEN_READY()
		{
			const DELAY = 500;

			while (SRV_STATUS_DOM !== undefined)
			{
				const SUCCESS = await AJAX_GET("/ajax/usermanagement/server_health");

				if (SUCCESS)
					location.reload();

				await new Promise((RESOLVE) => setTimeout(RESOLVE, DELAY));
			}
		}

		START_SERVER_WHEN_READY();

		return ;
	}

	switch(RESPONSE.THIS.error_level)
	{
		case (0): // ALREADY LOGIN
		{
			START_DESKTOP();
		}
		break ;
		case (5): // NOT LOGIN
		case (6): // LOGIN EXPIRED
		{
			RUN_APP("LOGIN");
		}
		break ;
		default: // INVALID OR UNEXPECTED ERROR
		{
			LOG(
				__LANG__[LANG].LOGIN.ERROR.UNDEXPECTED_START.MESSAGE +
					" (" +
					(RESPONSE.THIS.error_level || "?") +
					"): \n" + (RESPONSE.THIS.error_message || ""),
				"ERROR",
				{
					TITLE: __LANG__[LANG].LOGIN.ERROR.UNDEXPECTED_START.TITLE,
				}
			);
		}
	}
}
MAIN();


async function
	START_DESKTOP()
{
	const RESPONSE =
		await AJAX_SEND("/ajax/usermanagement/accessWithToken/", {});

	if (RESPONSE.STATUS || RESPONSE.THIS.error_level)
	{
		Object.entries(OS.PROCESS).forEach(
			function ([PID, APP])
			{
				CLOSE_WINDOW(PID);
			}
		);
		DESKTOP.THIS.classList.add("ERROR");
		LOG(
			__LANG__[LANG].LOGIN.ERROR.FORCE_START_ERROR.MESSAGE +
				" (" +
				(RESPONSE.THIS.error_level || "?") +
				"): \n" + (RESPONSE.THIS.error_message || ""),
			"ERROR",
			{
				TITLE: __LANG__[LANG].LOGIN.ERROR.FORCE_START_ERROR.TITLE,
				BUTTON_DISPLAY: false
			}
		);
		return ;
	}

	DESKTOP.THIS.classList.add("ACTIVE");
	window.history.pushState(
		{
			PAGE: "DESKTOP"
		},
		'',
		"/DESKTOP"
	);

	let START_BAR = document.createElement('DIV');

	START_BAR.id = "START_BAR";
	START_BAR.innerHTML =
		"<DIV ID='START_MENU'>" +
		 "<DIV CLASS='LEFT_BANNER'></DIV>" +
		 "<DIV CLASS='LIST'>" +
		  "<A ONCLICK='JAVASCRIPT:START_SETTINGS()'>" +
		   "<IMG SRC='/IMAGES/START/SETTINGS.png'/>" +
		   __LANG__[LANG].START.MENU.SETTINGS +
		  "</A>" +
		  "<SEPERATOR></SEPERATOR>" +
		  "<A ONCLICK='JAVASCRIPT:START_LOGOUT()'>" +
		   "<IMG SRC='/IMAGES/START/LOGOUT.png'/>" +
		   __LANG__[LANG].START.MENU.LOGOFF +
		  "</A>" +
		 "</DIV>" +
		"</DIV>" +
		"<DIV CLASS='LEFT'>" +
		 "<DIV CLASS='START'>" +
		  "<A ID='START' ONCLICK='JAVASCRIPT:START_CLICKED()'>" +
		   "<IMG SRC='/IMAGES/FAVICONS/favicon-16x16.png'/>" +
		   __LANG__[LANG].START.BUTTON_TEXT +
		  "</A>" +
		 "</DIV>" +
		 "<SEPERATOR_TOP></SEPERATOR_TOP>" +
		 "<SEPERATOR_BOX_TOP></SEPERATOR_BOX_TOP>" +
		"</DIV>" +
		"<DIV CLASS='MIDDLE'>" +
		"</DIV>" +
		"<DIV CLASS='RIGHT'>" +
		 "<SEPERATOR_TOP></SEPERATOR_TOP>" +
		 "<DIV CLASS='INFORMATION_AREA'>" + 
		  "<IMG " +
		   "SRC='/IMAGES/START/SRV_ONLINE.png' " +
		   "ALT='SERVER STATUS' " +
		   "ID='SRV_STATUS'" +
		  "/>" +
		  "<DIV CLASS='CLOCK'>" + 
		   "<SPAN ID='CLOCK_HOUR'>??</SPAN>" +
		   "<SPAN>/</SPAN>" +
		   "<SPAN ID='CLOCK_MINUTE'>??</SPAN>" +
		   "<SPAN>/</SPAN>" +
		   "<SPAN ID='CLOCK_SECOND'>??</SPAN>" +
		  "</DIV>" +
		 "</DIV>" +
		"</DIV>";

	SRV_STATUS_DOM = document.getElementById("SRV_STATUS");
	DESKTOP.THIS.appendChild(START_BAR);

	{ // CREATE APPS ON DESKTOP
		var APPS = "";

		Object.entries(OS.APP).forEach(
			function ([NAME, APP])
			{
				if (APP.DESKTOP.VISIBLE === true)
				{
					APPS +=
						"<DIV " +
						 "CLASS='APP'" +
						 "ONCLICK='JAVASCRIPT:FOCUS_APP(this)'" +
						 "ONDBLCLICK='JAVASCRIPT:RUN_APP(" +
						  "\"" + NAME + "\"" +
						 ");'" +
						">" +
						 "<IMG SRC='" + APP.PATH + "ICON.png" + "'/>" +
						 "<SPAN>" + NAME + "</SPAN>" +
						"</DIV>";
				}
			}
		);

		DESKTOP.APPS.innerHTML = APPS;
	} // CREATE APPS ON DESKTOP 

	UPDATE_CLOCK();
	TIME_INTERVAL = setInterval(UPDATE_CLOCK, 1000);
	CHECK_SERVER_STATUS();
}
