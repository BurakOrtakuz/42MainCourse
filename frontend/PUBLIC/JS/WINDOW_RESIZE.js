/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WINDOW_RESIZE.js                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

function
	PUSH_SIZE_WINDOW(THIS, PID, EVENT) /* ONMOUSEDOWN */
{
	const PROCESS = OS.PROCESS[PID];
	const DOM = PROCESS.THIS;

	if (!DOM)
	{
		BSOD("PUSH_SIZE_WINDOW: Invalid PID");
		return;
	}

	const RECTANGLE = DOM.getBoundingClientRect();

	MOUSE_EVENT.WINDOW.RESIZE_ID = THIS.id;
	MOUSE_EVENT.MOUSE.X = EVENT.clientX;
	MOUSE_EVENT.MOUSE.Y = EVENT.clientY;
	MOUSE_EVENT.WINDOW.X = RECTANGLE.left;
	MOUSE_EVENT.WINDOW.Y = RECTANGLE.top;
	MOUSE_EVENT.WINDOW.WIDTH = RECTANGLE.width;
	MOUSE_EVENT.WINDOW.HEIGHT = RECTANGLE.height;
	MOUSE_EVENT.WINDOW.THIS = DOM;
	MOVING_OR_RESIZING_WINDOW_PID = PID;
	document.addEventListener("mousemove", RESIZE_WINDOW);
}

function
	POP_SIZE_WINDOW(PID) /* ONMOUSEUP */
{
	document.removeEventListener("mousemove", RESIZE_WINDOW);
	MOUSE_EVENT.WINDOW.THIS = undefined;

	const PROCESS = OS.PROCESS[PID];

	if (!PROCESS)
		return ;

	const DOM = PROCESS.THIS;
	MOVING_OR_RESIZING_WINDOW_PID = -1;

	if (!DOM) // ??? How the fuck?
	{
		BSOD("Blue screen because fuck you - POP_SIZE_WINDOW: Invalid PID");
		return ;
	}

	const RECTANGLE = DOM.getBoundingClientRect();

	if (RECTANGLE.left < 0)
		DOM.style.left = "0";

	if (RECTANGLE.top < 0)
		DOM.style.top = "0";

	if (RECTANGLE.right > window.innerWidth)
		DOM.style.left = (window.innerWidth - RECTANGLE.width) + "PX";

	if (RECTANGLE.bottom > window.innerHeight)
		DOM.style.top = (window.innerHeight - RECTANGLE.height) + "PX";
}

function
	RESIZE_WINDOW(EVENT) /* mousemove */
{
	const DOM = MOUSE_EVENT.WINDOW.THIS;

	if (!DOM)
		return ;

	const SELECTION = window.getSelection();

	if (SELECTION)
		SELECTION.removeAllRanges();

	if (document.activeElement)
		document.activeElement.blur();

	const DELTA_X = EVENT.clientX - MOUSE_EVENT.MOUSE.X;
	const DELTA_Y = EVENT.clientY - MOUSE_EVENT.MOUSE.Y;

	const TITLE_BAR = DOM.querySelectorAll(".OS_WINDOW_TITLEBAR")[0];
	const TITLE_BAR_HEIGHT = TITLE_BAR.getBoundingClientRect().height + 4;
	let TITLE_BAR_WIDTH =
	(
		TITLE_BAR.querySelectorAll(
			".OS_WINDOW_TITLE"
		)[0].getBoundingClientRect().width +
		TITLE_BAR.querySelectorAll(
			".OS_WINDOW_CLOSE_BUTTON"
		)[0].getBoundingClientRect().width +
		TITLE_BAR.querySelectorAll(	
			".OS_WINDOW_MAXIMIZE_BUTTON"
		)[0].getBoundingClientRect().width +
		TITLE_BAR.querySelectorAll(
			".OS_WINDOW_MINIMIZE_BUTTON"
		)[0].getBoundingClientRect().width + 26
	);

	{
		const ICON_DOMS = TITLE_BAR.querySelectorAll(".OS_WINDOW_ICON");

		if (ICON_DOMS && ICON_DOMS[0])
			TITLE_BAR_WIDTH += ICON_DOMS[0].getBoundingClientRect().width;
	}

	switch (MOUSE_EVENT.WINDOW.RESIZE_ID)
	{
		case ("WINDOW-TOP-LEFT"):
		{
			if ((MOUSE_EVENT.WINDOW.WIDTH - DELTA_X) > TITLE_BAR_WIDTH)
				DOM.style.width = (MOUSE_EVENT.WINDOW.WIDTH - DELTA_X) + "PX";
			else
				MOUSE_EVENT.WINDOW.WIDTH = DELTA_X + TITLE_BAR_WIDTH;

			if ((MOUSE_EVENT.WINDOW.HEIGHT - DELTA_Y) > TITLE_BAR_HEIGHT)
				DOM.style.height = (MOUSE_EVENT.WINDOW.HEIGHT - DELTA_Y) + "PX";
			else
				MOUSE_EVENT.WINDOW.HEIGHT = DELTA_Y + TITLE_BAR_HEIGHT;

			DOM.style.left = (MOUSE_EVENT.WINDOW.X + DELTA_X) + "PX";
			DOM.style.top = (MOUSE_EVENT.WINDOW.Y + DELTA_Y) + "PX";
		}
		break ;
		case ("WINDOW-TOP-RIGHT"):
		{
			if ((MOUSE_EVENT.WINDOW.WIDTH + DELTA_X) > TITLE_BAR_WIDTH)
				DOM.style.width = (MOUSE_EVENT.WINDOW.WIDTH + DELTA_X) + "PX";

			if ((MOUSE_EVENT.WINDOW.HEIGHT - DELTA_Y) > TITLE_BAR_HEIGHT)
				DOM.style.height = (MOUSE_EVENT.WINDOW.HEIGHT - DELTA_Y) + "PX";
			else
				MOUSE_EVENT.WINDOW.HEIGHT = DELTA_Y + TITLE_BAR_HEIGHT;

			DOM.style.top = (MOUSE_EVENT.WINDOW.Y + DELTA_Y) + "PX";
		}
		break ;
		case ("WINDOW-BOTTOM-LEFT"):
		{
			if ((MOUSE_EVENT.WINDOW.WIDTH - DELTA_X) > TITLE_BAR_WIDTH)
				DOM.style.width = (MOUSE_EVENT.WINDOW.WIDTH - DELTA_X) + "PX";
			else
				MOUSE_EVENT.WINDOW.WIDTH = DELTA_X + TITLE_BAR_WIDTH;

			if ((MOUSE_EVENT.WINDOW.HEIGHT + DELTA_Y) > TITLE_BAR_HEIGHT)
				DOM.style.height = (MOUSE_EVENT.WINDOW.HEIGHT + DELTA_Y) + "PX";

			DOM.style.left = (MOUSE_EVENT.WINDOW.X + DELTA_X) + "PX";
		}
		break ;
		case ("WINDOW-BOTTOM-RIGHT"):
		{
			if ((MOUSE_EVENT.WINDOW.WIDTH + DELTA_X) > TITLE_BAR_WIDTH)
				DOM.style.width = (MOUSE_EVENT.WINDOW.WIDTH + DELTA_X) + "PX";

			if ((MOUSE_EVENT.WINDOW.HEIGHT + DELTA_Y) > TITLE_BAR_HEIGHT)
				DOM.style.height = (MOUSE_EVENT.WINDOW.HEIGHT + DELTA_Y) + "PX";
		}
		break ;
		case ("WINDOW-TOP"):
		{
			if ((MOUSE_EVENT.WINDOW.HEIGHT - DELTA_Y) > TITLE_BAR_HEIGHT)
				DOM.style.height = (MOUSE_EVENT.WINDOW.HEIGHT - DELTA_Y) + "PX";
			else
				MOUSE_EVENT.WINDOW.HEIGHT = DELTA_Y + TITLE_BAR_HEIGHT;

			DOM.style.top = (MOUSE_EVENT.WINDOW.Y + DELTA_Y) + "PX";
		}
		break ;
		case ("WINDOW-BOTTOM"):
		{
			if ((MOUSE_EVENT.WINDOW.HEIGHT + DELTA_Y) > TITLE_BAR_HEIGHT)
				DOM.style.height = (MOUSE_EVENT.WINDOW.HEIGHT + DELTA_Y) + "PX";
		}
		break ;
		case ("WINDOW-LEFT"):
		{
			if ((MOUSE_EVENT.WINDOW.WIDTH - DELTA_X) > TITLE_BAR_WIDTH)
				DOM.style.width = (MOUSE_EVENT.WINDOW.WIDTH - DELTA_X) + "PX";
			else
				MOUSE_EVENT.WINDOW.WIDTH = DELTA_X + TITLE_BAR_WIDTH;

			DOM.style.left = (MOUSE_EVENT.WINDOW.X + DELTA_X) + "PX";
		}
		break ;
		case ("WINDOW-RIGHT"):
		{
			if ((MOUSE_EVENT.WINDOW.WIDTH + DELTA_X) > TITLE_BAR_WIDTH)
				DOM.style.width = (MOUSE_EVENT.WINDOW.WIDTH + DELTA_X) + "PX";
		}
		break ;
	}
}
