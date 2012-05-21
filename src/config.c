/*
 * config.c - APme: Aion Automatic Abyss Point Tracker
 *
 * Copyright (C) 2012 Mitja Horvat <pinkfluid@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 */

/**
 * @file
 * Configuration related functions
 * 
 * @author Mitja Horvat <pinkfluid@gmail.com>
 */
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>

#include "iniparser.h"
#include "config.h"
#include "util.h"
#include "console.h"
#include "aion.h"

/**
 * @defgroup config Configuration Management
 *
 * @{
 */

/** The configuration database */
static dictionary *cfg_db = NULL;

static bool cfg_ini_path(char *inifile, size_t inifile_sz);

/**
 * Initialize the configuration sub-system
 */
bool cfg_init(void)
{
    return cfg_load();
}

/**
 * Load the configuration from the default INI file and initialize the global 
 * variables 
 */
bool cfg_load(void)
{
    char inifile[UTIL_MAX_PATH];
    dictionary *dini;

    con_printf("Loading configuration.\n");

    if (!cfg_ini_path(inifile, sizeof(inifile)))
    {
        con_printf("cfg_load() was unable to deterimine the inifile path");
    }

    dini = iniparser_load(inifile);
    if (dini == NULL)
    {
        con_printf("iniparser_load() failed on '%s'\n", inifile);
        return false;
    }

    /* Parse the values */
    iniparser_freedict(dini);

    con_printf("Configuration loaded successfully.\n");

    return true;
}

/**
 * Saves the current configuration to the config file
 */

bool cfg_store(void)
{
    if (cfg_db == NULL)
    {
        return false;
    }

    return true;
}

void cfg_set_string(char *section, char *name, char *value)
{
    char key[CFG_KEYSZ];

    con_printf("cfg_set_string(): Storing %s:%s -> %s\n", section, key, value);

    if (cfg_db == NULL)
    {
        con_printf("No configuration loaded.\n");
        return;
    }

    key[0] = '\0';
    util_strlcat(key, section, sizeof(key));
    util_strlcat(key, ":", sizeof(key));
    util_strlcat(key, name, sizeof(key));

    if (iniparser_set(cfg_db, key, value) != 0)
    {
        con_printf("cfg_set_string(): iniparser_set() failed\n");
    }
}

void cfg_set_int(char *section, char *key, int value)
{
    char strval[64];

    snprintf(strval, sizeof(strval), "%d", value);

    cfg_set_string(section, key, strval);
}

/**
 * Get the location of the INI file, create it if it does not exist
 *
 * @param[out]          inifile     Path to the configuration INI file
 * @param[in]           inifile_sz  Maximum number of bytes available in @p inifile
 *
 * @retval              true        On success
 * @retval              false       On erorr
 */
bool cfg_ini_path(char *inifile, size_t inifile_sz)
{
    FILE *fini;

    if (!sys_appdata_path(inifile, inifile_sz))
    {
        con_printf("cfg_load() was unable to retrieve the config data\n");
        return false;
    }

    /* Append the apme */
    util_strlcat(inifile, "/", inifile_sz);
    util_strlcat(inifile, CFG_APME_INI, inifile_sz);

    con_printf("INI file path: %s\n", inifile);

    /* Create the file if it does not exist */
    fini = fopen(inifile, "w+");
    if (fini == NULL)
    {
        con_printf("Unable to create the ini file: %s\n", strerror(errno));
        return false;
    }
    fclose(fini);

    return true;
}

/**
 * @}
 */
