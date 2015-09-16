/*
 * DistSCM.cc
 *
 * 
 * Copyright (C) 2015 OpenCog Foundation
 *
 * Author: Mandeep Singh Bhatia , September 2015
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License v3 as
 * published by the Free Software Foundation and including the exceptions
 * at http://opencog.org/wiki/Licenses
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to:
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include "DistSCM.h"
using namespace opencog;

DistSCM::DistSCM(void):true_string("true") 
{
  scm_with_guile(init_in_guile, this);	
}
void* DistSCM::init_in_guile(void* self)
{
    scm_c_define_module("opencog dist-gearman", init_in_module, self);
    scm_c_use_module("opencog dist-gearman");
    return NULL;
}
void DistSCM::init_in_module(void* data)
{
    DistSCM* self = (DistSCM*) data;
    self->init();
}
void DistSCM::init(void)
{
#ifdef HAVE_GUILE
	define_scheme_primitive("set-master-ip", &DistSCM::dist_master_ip,//master ip addr
                            this, "dist-gearman");
                            //if master ip is empty string then make this a slave
/*	define_scheme_primitive("set-this-as-slave", &DistSCM::dist_worker,//true/false
                            this, "dist-gearman");
    define_scheme_primitive("set-this-as-master", &DistSCM::dist_set_client,//true,false
                            this, "dist-gearman");
*/
    define_scheme_primitive("dist-run-scm", &DistSCM::dist_scm,
                            this, "dist-gearman");
    //there will be a slave-run-scm non scheme primitive gearman worker active if is set as a slave
#endif
}
const std::string& DistSCM::dist_master_ip(const std::string& ip_string)
{
	return ip_string;
}
const std::string& DistSCM::dist_scm(const std::string& scm_string)
{
	
	
	return true_string;
}
DistSCM::~DistSCM()
{
}
void opencog_dist_init(void)
{
	static DistSCM patty;
}
