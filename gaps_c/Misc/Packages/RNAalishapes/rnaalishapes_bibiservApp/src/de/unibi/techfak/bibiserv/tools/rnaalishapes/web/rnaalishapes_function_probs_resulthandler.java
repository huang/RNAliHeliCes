/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS HEADER.
 *
 * Copyright 2010 BiBiServ Curator Team, http://bibiserv.cebitec.uni-bielefeld.de,
 * All rights reserved.
 *
 * The contents of this file are subject to the terms of the Common
 * Development and Distribution License("CDDL") (the "License"). You
 * may not use this file except in compliance with the License. You can
 * obtain a copy of the License at http://www.sun.com/cddl/cddl.html
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.  When distributing the software, include
 * this License Header Notice in each file.  If applicable, add the following
 * below the License Header, with the fields enclosed by brackets [] replaced
 *  by your own identifying information:
 *
 * "Portions Copyrighted 2010 BiBiServ Curator Team, http://bibiserv.cebitec.uni-bielefeld.de"
 *
 * Contributor(s): 
 *
 */
package  de.unibi.techfak.bibiserv.tools.rnaalishapes.web;


import de.unibi.techfak.bibiserv.web.beans.session.AbstractResultHandlingBean;
import org.springframework.beans.factory.DisposableBean;
import org.springframework.beans.factory.InitializingBean;

/**
 * This is a autogenerated bean result handler template class for function <i>rnaalishapes_function_probs_resulthandler</i>
 *
 * @author Thomas Gatter - tgatter(at)cebitec.uni-bielefeld.de
 */
public class rnaalishapes_function_probs_resulthandler extends AbstractResultHandlingBean {

     /**
     * Return Id of input represented by this InputBean.
     *
     * @return Return ID of input
     */
    public String getId() {
        return "rnaalishapes_function_probs_resulthandler";
    }
    
    
    /**
     * Return if the function to keep the file on the server is disabled.
     * TODO: TG 12/2012: change if files are too big to keep on server!
     * @return 
     */
    public boolean isDownloadDisabled(){
        return false;
    }
    
    
     /**
     * Return if the function to upload the file to s3 is disabled.
     * @return 
     */
    public boolean isUploadDisabled(){
        return false;
    }
}
