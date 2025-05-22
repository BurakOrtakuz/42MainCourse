/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_API.js                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:00:03 by hdeniz            #+#    #+#             */
/*   Updated: 2024/02/01 18:00:29 by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

async function
	SLEEP(MS)
{
	return (new Promise(RESOLVE => setTimeout(RESOLVE, MS)));
}

async function
	CHECKOAUTH()
{
	localStorage.removeItem('CODE');
	const PARAMS = new URLSearchParams(window.location.search);
	const CODE = PARAMS.get('code');

	if (CODE === null)
		return ;

	localStorage.setItem('CODE', CODE);
	await SLEEP(50);
	window.close();
}

/* BOOL */ async function
	OAUTH42(PID)
{
	try
	{
		const RESPONSE = JSON.parse(
			await AJAX_GET("/ajax/usermanagement/intra_url")
		);

		return (OPENPOPUP(RESPONSE.URL, PID));
	}
	catch (ERROR)
	{
		LOG(
			__LANG__[LANG].LOGIN.ERROR.INTRA.MESSAGE +
			" (-1): " + ERROR,
			"ERROR",
			{
				TITLE: __LANG__[LANG].LOGIN.ERROR.INTRA.TITLE
			},
			PID
		);
		return (false);
	}
}

/* BOOL */ async function
	OPENPOPUP(URL, PID)
{
	window.open(URL, '42 Intra', 'width=800,height=600');
	const DATA = {CODE:''};

	const INTERVAL = setInterval(
		function ()
		{
			const CODE = localStorage.getItem('CODE');
			if (CODE !== null)
			{
				DATA.CODE = CODE;
				clearInterval(INTERVAL);
			}
		}, 100
	);

	while (DATA.CODE === '')
		await SLEEP(10);
	localStorage.removeItem('CODE');

	return (await INTRAVERIFY(DATA.CODE, PID));
}

/* BOOL */ async function
	INTRAVERIFY(CODE, PID)
{
	try
	{
		const RESPONSE =
			await AJAX_SEND("/ajax/usermanagement/intra_login/",
			{
				CODE: CODE
			}
		);

		if (
			RESPONSE.THIS.USERDATA &&
			RESPONSE.THIS.USERDATA.login === undefined
		)
		{
			const STATUS =
				(
					RESPONSE.THIS &&
					RESPONSE.THIS.USERDATA &&
					RESPONSE.THIS.USERDATA.status
				) || RESPONSE.THIS.error_level || "-1";
			const ERROR =
				(
					RESPONSE.THIS &&
					RESPONSE.THIS.USERDATA &&
					RESPONSE.THIS.USERDATA.error
				) || RESPONSE.THIS.error_message || "";

			LOG(
				__LANG__[LANG].LOGIN.ERROR.INTRA.MESSAGE +
				" (" + STATUS +
				(ERROR === "" ? ")" : ")\n") + ERROR,
				"ERROR",
				{
					TITLE: __LANG__[LANG].LOGIN.ERROR.INTRA.TITLE
				},
				PID
			);
			return (false);
		}

		return (true);
	}
	catch (ERROR)
	{
		BSOD(ERROR);
		return (false);
	}
}
