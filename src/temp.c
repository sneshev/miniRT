// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   temp.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/01/18 19:33:12 by winnitytrin       #+#    #+#             */
// /*   Updated: 2026/01/27 17:36:41 by winnitytrin      ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minirt.h"

void show_progress_bar (int j) {
	j += 1;
	int progress = 100 * (j) / HEIGHT;
	char buf[64];
	int len = snprintf(buf, sizeof(buf), "\r%d%% (%d / %d rays)", progress, j * WIDTH * RAYSPERPIXEL, HEIGHT * WIDTH * RAYSPERPIXEL);
	write(STDERR_FILENO, buf, len);
}
