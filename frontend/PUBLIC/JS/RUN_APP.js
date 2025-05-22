/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RUN_APP.js                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRING */ function // RETURNS PID
	RUN_APP(APP, META = {}, ARG = {}, PID = undefined)
{
	var NEW_WINDOW_CONTENTS = "";
	var NEW_APP_OBJECT = {};
	let CONTENT = "";
	let __META__ = {};

	if (OS.APP[APP].META && OS.APP[APP].META !== "")
	{
		__META__ = INTERPOLATE_VARIABLES_TO_STRING(
			OS.APP[APP].META,
			{
				ARG: ARG,
				LANG: __LANG__[LANG]
			}
		);

		try
		{
			__META__ = JSON.parse(__META__);
		}
		catch (ERROR)
		{
			BSOD("ERROR - While parsing JSON: " + ERROR);
		}
	}

	META.TITLE = META.TITLE || __META__.TITLE || "";
	META.ICON = META.ICON || __META__.ICON || undefined;
	META.BUTTON_MINIMIZE = META.BUTTON_MINIMIZE ||
		__META__.BUTTON_MINIMIZE || false;
	META.BUTTON_SIZE = META.BUTTON_SIZE || __META__.BUTTON_SIZE || false;
	META.BUTTON_CLOSE = META.BUTTON_CLOSE || __META__.BUTTON_CLOSE || false;
	META.RESIZE = META.RESIZE || __META__.RESIZE || false;
	META.WIDTH = META.WIDTH || __META__.WIDTH || "INITIAL";
	META.HEIGHT = META.HEIGHT || __META__.HEIGHT || "INITIAL";
	META.X = META.X || __META__.X || 0;
	META.Y = META.Y || __META__.Y || 0;

	NEW_APP_OBJECT.SIZEABLE = META.BUTTON_SIZE;

	if (META.FROM_PID && OS.PROCESS[META.FROM_PID])
	{
		const RECTANGLE =
			OS.PROCESS[META.FROM_PID].THIS.getBoundingClientRect();

		META.X = RECTANGLE.left + 26;
		META.Y = RECTANGLE.top + 26;
	}

	if (typeof(META.X) === "string" && META.X.toUpperCase() === "CENTER")
	{
		if (typeof(META.WIDTH) === "number")
			META.X = (window.innerWidth - META.WIDTH) / 2;
		else
			META.X = (window.innerWidth - 140) / 2;
	}

	if (typeof(META.Y) === "string" && META.Y.toUpperCase() === "CENTER")
	{
		if (typeof(META.HEIGHT) === "number")
			META.Y = (window.innerHeight - META.HEIGHT) / 2;
		else
			META.Y = (window.innerHeight - 140) / 2;
	}

	NEW_APP_OBJECT.Z_INDEX = Object.keys(OS.PROCESS).length + 1;
	NEW_APP_OBJECT.THIS = document.createElement("DIV");
	NEW_APP_OBJECT.THIS.classList.add("OS_WINDOW");
	NEW_APP_OBJECT.THIS.style.zIndex = NEW_APP_OBJECT.Z_INDEX;
	NEW_APP_OBJECT.ICON = undefined;

	if (typeof(META.WIDTH) === "number")
		NEW_APP_OBJECT.THIS.style.width = META.WIDTH + "PX";
	else
		NEW_APP_OBJECT.THIS.style.width = META.WIDTH;

	if (typeof(META.HEIGHT) === "number")
		NEW_APP_OBJECT.THIS.style.height = META.HEIGHT + "PX";
	else
		NEW_APP_OBJECT.THIS.style.height = META.HEIGHT;

	if (typeof(META.X) === "number")
		NEW_APP_OBJECT.THIS.style.left = META.X + "PX";
	else
		NEW_APP_OBJECT.THIS.style.left = META.X;

	if (typeof(META.Y) === "number")
		NEW_APP_OBJECT.THIS.style.top = META.Y + "PX";
	else
		NEW_APP_OBJECT.THIS.style.top = META.Y;

	if (PID === undefined)
	{
		/* NUMBER */ function
			RANDOM_NUMBER(MAX)
		{
			return (Math.floor(Math.random() * MAX));
		}

		let NUMBER_OF_TRIES = 0;

		while (1)
		{ // THIS IS SHIT
			PID = RANDOM_NUMBER(100000).toString();

			if (typeof(OS.PROCESS[PID]) === "undefined")
				break ;

			++NUMBER_OF_TRIES;

			if (NUMBER_OF_TRIES > 10000)
			{
				BSOD(
					"ERROR - FAILED TO CREATE WINDOW:" +
					"(Reached Try Limit)"
				);
				break ;
			}
		}
	}

	if (OS.APP[APP])
		ARG.PWD = OS.APP[APP].PATH
	else
		ARG.PWD = "/"

	ARG.PID = PID;
	ARG.LANG = __LANG__[LANG];

	if (OS.APP[APP])
	{
		CONTENT =
			INTERPOLATE_VARIABLES_TO_STRING(OS.APP[APP].THIS, ARG); // HOLY COW
	}
	else
		CONTENT = INTERPOLATE_VARIABLES_TO_STRING(APP, ARG); // HOLY COW 2

	if (META.RESIZE)
	{
		NEW_WINDOW_CONTENTS +=
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-TOP-LEFT'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>" +
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-TOP-RIGHT'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>" +
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-BOTTOM-LEFT'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>" +
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-BOTTOM-RIGHT'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>" +
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-TOP'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>" +
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-BOTTOM'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>" +
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-LEFT'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>" +
			"<DIV CLASS='OS_WINDOW_RESIZER_OBJECT' ID='WINDOW-RIGHT'" +
			"ONMOUSEDOWN='" +
			 "JAVASCRIPT:PUSH_SIZE_WINDOW(this, " + PID + ", event)'" +
			"ONMOUSEUP='JAVASCRIPT:POP_SIZE_WINDOW(" + PID + ")'></DIV>"
	}

	NEW_WINDOW_CONTENTS +=
		'<DIV CLASS="OS_WINDOW_BORDER"' +
		 'ONMOUSEDOWN="JAVASCRIPT:SET_WINDOW_POSITION(event, ' + PID + ')"' +
		 'ONMOUSEUP="JAVASCRIPT:WINDOW_STOPPED_MOVING(' + PID + ')"' +
		'>' +
		 '<DIV CLASS="OS_WINDOW_TITLEBAR"' +
		  'ONDBLCLICK="JAVASCRIPT:TITLE_BAR_DOUBLE_CLICK(' + PID + ')"' +
		 '>';

	if (META.ICON)
	{
		NEW_APP_OBJECT.ICON = OS.APP[APP].PATH + "FAVICON.png";
		NEW_WINDOW_CONTENTS +=
			'<IMG CLASS="OS_WINDOW_ICON" SRC="' +
			NEW_APP_OBJECT.ICON +
			'"/>';
	}

	NEW_APP_OBJECT.THIS.onmousedown = (
		function ()
		{
			UPDATE_WINDOW_HEADER(PID);
			FOCUS_ON_WINDOW(PID);
		}
	);

	NEW_WINDOW_CONTENTS +=
		'<SPAN ID="__' + PID + '__APP_TITLE" CLASS="OS_WINDOW_TITLE">' +
		 META.TITLE +
		'</SPAN>';

	if (!META.BUTTON_CLOSE)
		NEW_WINDOW_CONTENTS += '<SPAN CLASS="OS_WINDOW_CLOSE_BUTTON">r</SPAN>';
	else
		NEW_WINDOW_CONTENTS +=
			'<A CLASS="OS_WINDOW_CLOSE_BUTTON" ' +
			'ONCLICK="JAVASCRIPT:CLOSE_WINDOW(' + PID + ')">r</A>';

	if (!META.BUTTON_SIZE)
		NEW_WINDOW_CONTENTS +=
			'<SPAN CLASS="OS_WINDOW_MAXIMIZE_BUTTON">1</SPAN>';
	else
		NEW_WINDOW_CONTENTS += '<A CLASS="OS_WINDOW_MAXIMIZE_BUTTON" ' +
		 'ONCLICK="JAVASCRIPT:MAXIMIZE_RESTORE_WINDOW(' + PID + ');" ' +
		 '>1</A>';

	if (!META.BUTTON_MINIMIZE)
		NEW_WINDOW_CONTENTS +=
			  '<SPAN CLASS="OS_WINDOW_MINIMIZE_BUTTON">0</SPAN>';
	else
		NEW_WINDOW_CONTENTS +=
			  '<A CLASS="OS_WINDOW_MINIMIZE_BUTTON"' +
			   'ONCLICK="JAVASCRIPT:MINIMIZE_WINDOW(' + PID + ');">0' +
			  '</A>';

	NEW_WINDOW_CONTENTS +=
		 '</DIV>' +
		'</DIV>' +
		'<DIV CLASS="OS_WINDOW_INNER">' + CONTENT + '</DIV>';

	NEW_APP_OBJECT.WAITING_PID = "";
	NEW_APP_OBJECT.IS_TRIGGERING = false;
	NEW_APP_OBJECT.THIS.innerHTML = NEW_WINDOW_CONTENTS;
	NEW_APP_OBJECT.TITLE = META.TITLE;
	NEW_APP_OBJECT.TITLE_DOM =
		NEW_APP_OBJECT.THIS.querySelectorAll(".OS_WINDOW_TITLE")[0];
	SET_TAB_INDEXES(NEW_APP_OBJECT.THIS); // SET PERMA TABS
	OS.PROCESS[PID] = NEW_APP_OBJECT;
	NEW_APP_OBJECT.MAXIMIZE = false;
	NEW_APP_OBJECT.MINIMIZE = false;
	NEW_APP_OBJECT.WIDTH = 0;
	NEW_APP_OBJECT.HEIGHT = 0;
	NEW_APP_OBJECT.X = 0;
	NEW_APP_OBJECT.Y = 0;

	{ /* MAKE THE <SCRIPT> TAGS WORK INSIDE THE CONTENT */
		const SCRIPTS = NEW_APP_OBJECT.THIS.getElementsByTagName('SCRIPT');

		NEW_APP_OBJECT.ONBLUR = function (){};
		NEW_APP_OBJECT.ONFOCUS = function (){};

		if (SCRIPTS)
		{
			for (let SCRIPT of SCRIPTS)
			{
				if (SCRIPT && SCRIPT.id === "DESTRUCTOR")
				{
					NEW_APP_OBJECT.DESTRUCTOR =
						new Function(SCRIPT.textContent);
				}
				else if (SCRIPT && SCRIPT.id === "ONFOCUS")
				{
					NEW_APP_OBJECT.ONFOCUS =
						new Function(SCRIPT.textContent);
				}
				else if (SCRIPT && SCRIPT.id === "ONBLUR")
				{
					NEW_APP_OBJECT.ONBLUR =
						new Function(SCRIPT.textContent);
				}
			}
		}
	} /* MAKE THE <SCRIPT> TAGS WORK INSIDE THE CONTENT */

	DESKTOP.WINDOWS.appendChild(NEW_APP_OBJECT.THIS);
	NEW_APP_OBJECT.TITLE_ELEMENT =
		document.getElementById("__" + PID + "__APP_TITLE");
	NEW_APP_OBJECT.SET_TITLE =
	(
		function (NEW_TITLE)
		{
			this.TITLE_ELEMENT.innerHTML = NEW_TITLE;
		}
	);

	{ /* MAKE THE FUNCTIONS SEENABLE FOR DOM ELEMENTS */
		const TEMP = document.createElement('DIV');

		TEMP.innerHTML = NEW_WINDOW_CONTENTS;

		const SCRIPTS = TEMP.getElementsByTagName('SCRIPT');

		if (SCRIPTS)
		{
			for (let SCRIPT of SCRIPTS)
			{
				if (
					SCRIPT &&
					(
						SCRIPT.id === "CONSTRUCTOR" ||
						SCRIPT.id === "EVENTS"
					)
				)
				{
					window.$EVAL(SCRIPT.innerHTML);
				}
			}
		}
	} /* MAKE THE FUNCTIONS SEENABLE FOR DOM ELEMENTS */

	FOCUS_ON_WINDOW(PID, false); // FOCUS ON WINDOW
	return (PID);
}

function
	RUN_AND_WAIT_APP(PID, APP, META = {}, ARG = {})
{
	if (PID === undefined || PID === 0)
	{
		META.X = META.X || "CENTER";
		META.Y = META.Y || "CENTER";
		RUN_APP(
			APP,
			META,
			ARG
		);
		return ;
	}

	const PROCESS = OS.PROCESS[PID];
	const RECTANGLE = PROCESS.THIS.getBoundingClientRect();

	META.X = META.X || RECTANGLE.left + 26;
	META.Y = META.Y || RECTANGLE.top + 26;
	ARG.PARENT_PID = PID;
	PROCESS.THIS.querySelectorAll("TEXTAREA, A").forEach(
		ELEMENT =>
		{
			ELEMENT.classList.add("UNSELECT");
		}
	);
	PROCESS.WAITING_PID = RUN_APP(
		APP,
		META,
		ARG
	);
}

function
	LOG(MESSAGE, TYPE = "INFO", META = {}, PID = 0)
{
	META.TITLE = META.TITLE || "Log";
	META.X = META.X || "CENTER";
	META.Y = META.Y || "CENTER";
	META.WIDTH = META.WIDTH || "INITIAL";
	META.HEIGHT = META.HEIGHT || "INITIAL";

	if (typeof(META.BUTTON_DISPLAY) !== "boolean")
		META.BUTTON_DISPLAY = true;

	if (typeof(META.CLOSE_PARENT) !== "boolean")
		META.CLOSE_PARENT = false;

	if (META.BUTTON_DISPLAY)
		META.BUTTON_DISPLAY = "BLOCK";
	else
		META.BUTTON_DISPLAY = "NONE";

	RUN_AND_WAIT_APP(
		PID,
		"POPUP",
		META,
		{
			TYPE: TYPE,
			MESSAGE: String(MESSAGE),
			BUTTON_DISPLAY: META.BUTTON_DISPLAY,
			CLOSE_PARENT: META.CLOSE_PARENT
		}		
	);
}
