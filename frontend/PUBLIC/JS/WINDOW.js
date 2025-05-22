/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WINDOW.js                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const OS =
{
	PROCESS: {},
	APP:
	{
		/*
			NAME: "",
			THIS: "",
			META: "",
			PATH: "",
			DESKTOP: {}
		*/
	}
};

var FOCUSED_PROCESS = undefined;

function
	CLOSE_WINDOW(PID)
{
	const PROCESS = OS.PROCESS[PID];

	if (PROCESS == undefined)
	{
		BSOD({message: "CLOSE_WINDOW(" + PID + ")"});
		return ;
	}

	if (PID == FOCUSED_PROCESS)
		FOCUSED_PROCESS = undefined;

	UPDATE_WINDOW_HEADER();

	if (typeof(PROCESS.DESTRUCTOR) === "function")
		PROCESS.DESTRUCTOR();

	PROCESS.THIS.remove();
	delete OS.PROCESS[PID];
}

function
	TITLE_BAR_DOUBLE_CLICK(PID) /* ondblclick */
{
	const PROCESS = OS.PROCESS[PID];

	if (!PROCESS)
		return ;

	let __MAXIMIZE_RESTORE_BUTTON__ =
		PROCESS.THIS.querySelectorAll(".OS_WINDOW_MAXIMIZE_BUTTON");

	if (PROCESS.WAITING_PID || PROCESS.SIZEABLE === false)
		return ;

	if (__MAXIMIZE_RESTORE_BUTTON__)
		__MAXIMIZE_RESTORE_BUTTON__ = __MAXIMIZE_RESTORE_BUTTON__[0];

	if (PROCESS.MAXIMIZE)
	{
		PROCESS.MAXIMIZE = false;
		PROCESS.THIS.style.width = PROCESS.WIDTH + "PX";
		PROCESS.THIS.style.height = PROCESS.HEIGHT + "PX";
		PROCESS.THIS.style.left = PROCESS.X + "PX";
		PROCESS.THIS.style.top = PROCESS.Y + "PX";
		__MAXIMIZE_RESTORE_BUTTON__.textContent = "1";
		PROCESS.THIS.querySelectorAll(".OS_WINDOW_RESIZER_OBJECT").forEach(
			function (ELEMENT)
			{
				ELEMENT.style.display = "BLOCK";
			}
		);
	}
	else
	{
		const SIZES = PROCESS.THIS.getBoundingClientRect();

		PROCESS.MAXIMIZE = true;
		PROCESS.WIDTH = SIZES.width;
		PROCESS.HEIGHT = SIZES.height;
		PROCESS.X = SIZES.left;
		PROCESS.Y = SIZES.top;
		PROCESS.THIS.style.width = "100%";
		PROCESS.THIS.style.height = "100%";
		PROCESS.THIS.style.left = "0";
		PROCESS.THIS.style.top = "0";
		__MAXIMIZE_RESTORE_BUTTON__.textContent = "2";
		PROCESS.THIS.querySelectorAll(".OS_WINDOW_RESIZER_OBJECT").forEach(
			function (ELEMENT)
			{
				ELEMENT.style.display = "NONE";
			}
		);
	}
}

function
	MAXIMIZE_RESTORE_WINDOW(PID)
{
	const PROCESS = OS.PROCESS[PID];
	var __MAXIMIZE_RESTORE_BUTTON__ =
		PROCESS.THIS.querySelectorAll(".OS_WINDOW_MAXIMIZE_BUTTON");

	if (PROCESS.WAITING_PID)
		return ;

	if (__MAXIMIZE_RESTORE_BUTTON__)
		__MAXIMIZE_RESTORE_BUTTON__ = __MAXIMIZE_RESTORE_BUTTON__[0];

	if (PROCESS.MAXIMIZE)
	{
		PROCESS.MAXIMIZE = false;
		PROCESS.THIS.style.width = PROCESS.WIDTH + "PX";
		PROCESS.THIS.style.height = PROCESS.HEIGHT + "PX";
		PROCESS.THIS.style.left = PROCESS.X + "PX";
		PROCESS.THIS.style.top = PROCESS.Y + "PX";
		__MAXIMIZE_RESTORE_BUTTON__.textContent = "1";
		PROCESS.THIS.querySelectorAll(".OS_WINDOW_RESIZER_OBJECT").forEach(
			function (ELEMENT)
			{
				ELEMENT.style.display = "BLOCK";
			}
		);
	}
	else
	{
		const SIZES = PROCESS.THIS.getBoundingClientRect();

		PROCESS.MAXIMIZE = true;
		PROCESS.WIDTH = SIZES.width;
		PROCESS.HEIGHT = SIZES.height;
		PROCESS.X = SIZES.left;
		PROCESS.Y = SIZES.top;
		PROCESS.THIS.style.width = "100%";
		PROCESS.THIS.style.height = "100%";
		PROCESS.THIS.style.left = "0";
		PROCESS.THIS.style.top = "0";
		__MAXIMIZE_RESTORE_BUTTON__.textContent = "2";
		PROCESS.THIS.querySelectorAll(".OS_WINDOW_RESIZER_OBJECT").forEach(
			function (ELEMENT)
			{
				ELEMENT.style.display = "NONE";
			}
		);
	}
}

function
	MINIMIZE_WINDOW(PID)
{
	const PROCESS = OS.PROCESS[PID];

	if (PROCESS.WAITING_PID)
		return ;

	// PROCESS.MINIMIZE = true;
}

function
	UPDATE_WINDOW_HEADER(PID = undefined)
{
	if (OS.PROCESS[PID] && OS.PROCESS[PID].WAITING_PID)
		return ;

	if (PID === undefined)
	{
		document.title = "Transcendence";
		CHANGE_FAVICON();
	}
	else
	{
		const PROCESS = OS.PROCESS[PID];

		if (PROCESS.ICON)
			CHANGE_FAVICON(PROCESS.ICON);
		else
			CHANGE_FAVICON();

		document.title = PROCESS.TITLE;
	}
}

function
	CHANGE_FAVICON(LINK = "/IMAGES/FAVICONS/favicon-16x16.png", SIZE = "16x16")
{
	var LINK_OBJECTS = document.querySelectorAll("LINK");
	var CORRECT_LINK_FOUND = false;

	if (LINK_OBJECTS.length > 0)
	{
		LINK_OBJECTS.forEach(
			function (OBJECT)
			{
				if (
					(
						OBJECT.rel === "icon" &&
						OBJECT.sizes && OBJECT.sizes.value === SIZE
					) ||
					(
						SIZE === "16x16" &&
						OBJECT.rel === "icon" &&
						!(
							OBJECT.sizes &&
							OBJECT.sizes.value !== ""
						)
					) ||
					(OBJECT.rel === "shortcut icon")
				)
				{
					CORRECT_LINK_FOUND = true;
					OBJECT.href = LINK;
				}
			}
		);
	}

	if (!CORRECT_LINK_FOUND)
	{
		LINK_OBJECTS = document.createElement('link');
		LINK_OBJECTS.rel = 'icon';
		LINK_OBJECTS.sizes = SIZE;
		LINK_OBJECTS.href = LINK;
		document.head.appendChild(LINK_OBJECTS);
	}
}

function
	SET_TITLE(TITLE, PID = undefined)
{
	if (PID === undefined)
	{
		document.title = TITLE;
		return ;
	}

	const PROCESS = OS.PROCESS[PID];

	if (!PROCESS)
		return ;

	PROCESS.TITLE = TITLE;
	PROCESS.TITLE_DOM.textContent = TITLE;

	if (document.title === PROCESS.TITLE)
		UPDATE_WINDOW_HEADER(PID);	
}

function
	FOCUS_ON_WINDOW(__PID__, NOT_ON_WINDOW_CREATING = true)
{
	let   PROCESS = OS.PROCESS[__PID__];
	const Z_INDEX_OF_PROCESS = PROCESS.Z_INDEX;
	const MAX_Z_INDEX_VALUE = Object.keys(OS.PROCESS).length;

	UNFOCUS_ON_DESKTOP_ICON();
	UPDATE_WINDOW_HEADER(__PID__);
	CLOSE_START_MENU();

	if (!NOT_ON_WINDOW_CREATING)
	{
		setTimeout(
			function()
			{
				if (
					PROCESS.THIS.querySelectorAll(
						"TEXTAREA, A.WINBUTTON"
					)[0]
				)
				{
					PROCESS.THIS.querySelectorAll(
						"TEXTAREA, A.WINBUTTON"
					)[0].focus();
				}
			}, 1
		);
	}

	if (
		NOT_ON_WINDOW_CREATING &&
		Z_INDEX_OF_PROCESS === MAX_Z_INDEX_VALUE &&
		__PID__ == FOCUSED_PROCESS
	)
		return ;

	if (PROCESS.WAITING_PID !== "")
	{
		if (
			typeof(
				OS.PROCESS[PROCESS.WAITING_PID]
			) === "undefined"
		)
			PROCESS.WAITING_PID = "";
		else
		{
			while (
				PROCESS.WAITING_PID &&
				typeof(
					OS.PROCESS[
						PROCESS.WAITING_PID
					]
				) !== "undefined"
			)
				PROCESS = OS.PROCESS[PROCESS.WAITING_PID];

			if (!PROCESS.IS_TRIGGERING)
			{
				let TOTAL_BLINKS = 0;
				const CONNECTED_WINDOW = PROCESS.THIS;
				const TITLE_ELEMENT = PROCESS.TITLE_ELEMENT;
				const ORG_COLOR = CONNECTED_WINDOW.style.color;

				PROCESS.IS_TRIGGERING = true;

				while (TOTAL_BLINKS < 14)
				{
					const COLOR =
						(TOTAL_BLINKS % 2 === 0 && "TRANSPARENT") || ORG_COLOR;

					setTimeout(
						function ()
						{
							TITLE_ELEMENT.style.color = COLOR;
							CONNECTED_WINDOW.style.color = COLOR;
						}, 30 * TOTAL_BLINKS
					);
					setTimeout(
						function ()
						{
							PROCESS.IS_TRIGGERING = false;
						}, 420
					);
					++TOTAL_BLINKS;
				}
			}

			return ;
		}
	}

	if (FOCUSED_PROCESS !== undefined)
	{
		FOCUSED_PROCESS = OS.PROCESS[FOCUSED_PROCESS];
		RESET_TABS(FOCUSED_PROCESS.THIS);
		FOCUSED_PROCESS.ONBLUR();
		FOCUSED_PROCESS = undefined;
	}

	FOCUSED_PROCESS = __PID__;
	PROCESS.ONFOCUS();

	Object.entries(OS.PROCESS).forEach(
		function ([PID, APP])
		{
			if (PID === __PID__)
			{
				APP.Z_INDEX = Object.keys(OS.PROCESS).length;
				APP.THIS.style.zIndex = APP.Z_INDEX;
				SET_TABS(APP.THIS);
			}
			else
			{
				if (Z_INDEX_OF_PROCESS < APP.Z_INDEX)
				{
					--APP.Z_INDEX;
					APP.THIS.style.zIndex = APP.Z_INDEX;
				}

				RESET_TABS(APP.THIS);
			}
		}
	);
}

function
	SET_TAB_INDEXES(__ELEMENT__)
{ // FOT [TAB] KEY, WHICH IS ACTUALLY FOCUS INDEX
	let TAB_INDEX = 1;

	if (!__ELEMENT__ || !(__ELEMENT__ instanceof Element))
	{
		BSOD("__ELEMENT__ is not a DOM element!");
		return ;
	}

	__ELEMENT__.querySelectorAll("A, TEXTAREA").forEach(
		function (ELEMENT)
		{
			ELEMENT.setAttribute("DATA-TABINDEX", TAB_INDEX);
			++TAB_INDEX;
		}
	);
} // THIS FUNCTION IS USED FOR CREATING PERMANENT TAB INDEXES

function
	SET_TABS(__ELEMENT__)
{
	const TITLE_BAR = __ELEMENT__.querySelectorAll(".OS_WINDOW_TITLEBAR")[0];

	TITLE_BAR.classList.add("FOCUS");
	__ELEMENT__.querySelectorAll("A, TEXTAREA").forEach(
		function (ELEMENT)
		{
			const DATA_TAB_INDEX = ELEMENT.getAttribute("DATA-TABINDEX");

			if (DATA_TAB_INDEX)
				ELEMENT.setAttribute("TABINDEX", DATA_TAB_INDEX);
		}
	);

	const FOCUSABLE_ELEMENTS =
		Array.from(__ELEMENT__.querySelectorAll("A, TEXTAREA"));

	FOCUSABLE_ELEMENTS.sort(
		(A, B) =>
			A.getAttribute("DATA-TABINDEX") - B.getAttribute("DATA-TABINDEX")
	);

	__ELEMENT__.onkeydown = (
		function (EVENT)
		{
			if (EVENT.key === "Tab")
			{
				EVENT.preventDefault();
				const CURRENT_INDEX =
					FOCUSABLE_ELEMENTS.indexOf(document.activeElement);
				const NEXT_INDEX =
					EVENT.shiftKey
					? (CURRENT_INDEX - 1 + FOCUSABLE_ELEMENTS.length) %
					FOCUSABLE_ELEMENTS.length
					: (CURRENT_INDEX + 1) % FOCUSABLE_ELEMENTS.length;
				FOCUSABLE_ELEMENTS[NEXT_INDEX].focus();
			}
			else if (EVENT.key === "Enter" || EVENT.key === " ")
			{
				const ACTIVE = document.activeElement;

				if (EVENT.key === "Enter")
					EVENT.preventDefault(); // DISABLE PUTTING A NEW LINE

				if (ACTIVE && typeof ACTIVE.onclick === "function")
					ACTIVE.onclick();
			}
		}
	);
}

function
	RESET_TABS(__ELEMENT__)
{
	const TITLE_BAR = __ELEMENT__.querySelectorAll(".OS_WINDOW_TITLEBAR")[0];

	TITLE_BAR.classList.remove("FOCUS");
	__ELEMENT__.onkeydown = (function (EVENT) {});
	__ELEMENT__.querySelectorAll("A, TEXTAREA").forEach(
		function (ELEMENT)
		{
			const DATA_TAB_INDEX = ELEMENT.getAttribute("DATA-TABINDEX");

			if (DATA_TAB_INDEX)
				ELEMENT.setAttribute("TABINDEX", -1);
		}
	);
}
