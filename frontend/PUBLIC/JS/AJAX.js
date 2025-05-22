/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AJAX.js                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 ??:??:?? by hdeniz            #+#    #+#             */
/*   Updated: 2024/11/01 ??:??:?? by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRING */ async function
	AJAX_GET(/* STRING */ SOURCE_URL)
{
	return (
		new Promise(
			function (RESOLVE, REJECT)
			{
				const XML_HTTP_REQUEST = new XMLHttpRequest();

				XML_HTTP_REQUEST.open("GET", SOURCE_URL);
				XML_HTTP_REQUEST.onreadystatechange = (
					function ()
					{
						if (XML_HTTP_REQUEST.readyState === 4)
						{
							if (XML_HTTP_REQUEST.status === 200)
							{
								SRV_STATUS("GET");
								RESOLVE(XML_HTTP_REQUEST.responseText);
							}
							else
								RESOLVE(undefined);
						}
					}
				);
				XML_HTTP_REQUEST.send();
			}
		)
	);
}

/* OBJECT */ async function
	AJAX_SEND(SOURCE, DATA = {})
{
	return (
		new Promise(
			function (RESOLVE)
			{
				const XML_HTTP_REQUEST = new XMLHttpRequest();

				XML_HTTP_REQUEST.open("POST", SOURCE, true);
				XML_HTTP_REQUEST.timeout = 0;
				XML_HTTP_REQUEST.setRequestHeader(
					"Content-Type",
					"application/json"
				);
				XML_HTTP_REQUEST.onreadystatechange = () =>
				{
					if (XML_HTTP_REQUEST.readyState === 4)
					{
						if (XML_HTTP_REQUEST.status === 200)
						{
							try
							{
								SRV_STATUS("GET");
								RESOLVE(
									{
										STATUS: 0,
										THIS: JSON.parse(
											XML_HTTP_REQUEST.responseText
										)
									}
								);
							}
							catch (ERROR)
							{
								RESOLVE(ERROR);
							}
						}
						else
						{
							let THIS = XML_HTTP_REQUEST.responseText;

							if (THIS)
							{
								try
								{
									THIS = JSON.parse(THIS);
								}
								catch (ERROR)
								{
									SRV_STATUS("GET");
									RESOLVE(
										{
											STATUS: XML_HTTP_REQUEST.status,
											MESSAGE: XML_HTTP_REQUEST.statusText
										}
									);
								}
							}

							SRV_STATUS("GET");
							RESOLVE(
								{
									STATUS: XML_HTTP_REQUEST.status,
									MESSAGE: XML_HTTP_REQUEST.statusText,
									THIS: THIS
								}
							);
						}
					}
				};

				try
				{
					if (DATA === {})
						SRV_STATUS("GET");
					else
						SRV_STATUS("SEND");

					XML_HTTP_REQUEST.send(JSON.stringify(DATA));
				}
				catch (SEND_ERROR)
				{
					SRV_STATUS("GET");
					RESOLVE(
						{
							STATUS: -1,
							MESSAGE: SEND_ERROR
						}
					);
				}
			}
		)
	);
}
