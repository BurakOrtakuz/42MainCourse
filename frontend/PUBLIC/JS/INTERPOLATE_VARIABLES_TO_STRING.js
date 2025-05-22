/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INTERPOLATE_VARIABLES_TO_STRING.js                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdeniz <Discord:@teomandeniz>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 ??:??:?? by hdeniz            #+#    #+#             */
/*   Updated: 2024/11/01 ??:??:?? by hdeniz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STRING */ function
	INTERPOLATE_VARIABLES_TO_STRING(STRING, OBJECT)
{
	function
		PROP(PROP_OBJECT, IS, VALUE)
	{
		if (typeof IS == 'string')
			IS = IS.split('.');

		if (IS.length == 1 && VALUE !== undefined)
			return (PROP_OBJECT[IS[0]] = VALUE);
		else if (IS.length == 0)
			return (PROP_OBJECT);
		else
		{
			var SHIFT = IS.shift();

			if (VALUE !== undefined && PROP_OBJECT[SHIFT] == undefined)
				PROP_OBJECT[SHIFT] = {};

			return (PROP(PROP_OBJECT[SHIFT], IS, VALUE));
		}
	}

	// HANDLE ARRAY-LIKE SYNTAX "$[ARRAY]{STRING @.PROPERYU STRING}""
	STRING = STRING.replace(
		/\$\[(.+?)\]\{(.+?)\}/g, (MATCH, ARRAY_PROP, TEMPLATE) =>
		{
			const ARRAY = PROP(OBJECT, ARRAY_PROP);

			if (Array.isArray(ARRAY))
			{
				return (
					ARRAY.map(ITEM =>
						{
							return (
								TEMPLATE.replace(
									/@\.(\w+)/g, (SUBMATCH, PROP_NAME) =>
									{
										return (PROP(ITEM, PROP_NAME));
									}
								)
							);
						}
					).join('')
				);
			}

			return (MATCH);
		}
	);
	return (STRING.replace(/\$\{(.+?)\}/g,
		(MATCH, THE_PROP) => PROP(OBJECT, THE_PROP)));
}
