void	Class_InverterAlg::Alg_Int_InvCurrRmsReg(void)
{
	INT16	i16_TmpRMSRef_0,i16_TmpAx_0,i16_TmpBx_0,i16_TmpCx_0,i16_TmpDx_0,i16_TmpKp_0,i16_TmpKi_0;
	
	i16_TmpRMSRef_0 = (((INT32)objInvCtrl.m_i16_IrefRunM_0 * 2897)>>12);	

	if(objInverter.m_st_FlagInv.bInv != 0
		&&objOutputXfer.m_st_OutputXferResult.bInvRelay == 1)
	{
		
		i16_TmpAx_0 = ((INT32)i16_TmpRMSRef_0 * 205)>>12;		
		i16_TmpBx_0 = 250;										
		i16_TmpCx_0 = MAX2(i16_TmpAx_0,i16_TmpBx_0);

		if(m_i16_IrefSetMBake != objInvCtrl.m_i16_IrefSetM)
		{
			if(objInvCtrl.m_i16_IrefSetM < 880					
				&&m_i32_R_0 >= 768)
			{
				m_un_IntgInvIRRms_0.half.hword = 1536;			
			}
			else if(objInvCtrl.m_i16_IrefSetM < 880				
					&&m_i32_R_0 >= 512)
			{
				m_un_IntgInvIRRms_0.half.hword = 1024;
			}
			else if(objInvCtrl.m_i16_IrefSetM < 880)
			{
				m_un_IntgInvIRRms_0.half.hword = 512;
			}
			else
			{
				m_un_IntgInvIRRms_0.dword = 0;
			}
		}
		else
		{
			
			if((abs(m_i16_IerrInvRms_0) >= i16_TmpCx_0)
				&&(m_i16_IerrInvRms_0 < 0)
				&&(m_un_IntgInvIRRms_0.dword > 0)
				&&(objInvCtrl.m_i16_IrefSetM > 2896)) 
			{
				m_un_IntgInvIRRms_0.dword -= 131070;
				if(m_un_IntgInvIRRms_0.dword < 0)
				{
					m_un_IntgInvIRRms_0.dword = 0;
				}
			}		
			if((abs(m_i16_IerrInvRms_0) >= i16_TmpCx_0)
				&&(m_i16_IerrInvRms_0 > 0)
				&&(m_un_IntgInvIRRms_0.dword < 0)
				&&(objInvCtrl.m_i16_IrefSetM > 2896))
			{
				m_un_IntgInvIRRms_0.dword += 16384;
				if(m_un_IntgInvIRRms_0.dword > 0)
				{
					m_un_IntgInvIRRms_0.dword = 0;
				}
			}
		}
		
		
		if(abs(m_i16_IerrInvRms_0) >= 250						
			&&(objInvCtrl.m_i16_IrefSetM > 2896))				
		{
			i16_TmpKp_0 = m_i16_KpInvCurrRmsReg_0 * 5;
		}
		else
		{
			i16_TmpKp_0 -= 5;
			if(i16_TmpKp_0 <= m_i16_KpInvCurrRmsReg_0)
			{
				i16_TmpKp_0 = m_i16_KpInvCurrRmsReg_0;
			}
		}
		
		
		if(objInvCtrl.m_i16_IrefSetM >= 614)					
		{
			i16_TmpKi_0 = m_i16_KiInvCurrRmsReg_0;
		}
		else if(objInvCtrl.m_i16_IrefSetM >= 351)				
		{
			i16_TmpKi_0 = m_i16_KiInvCurrRmsReg_0 + 20;			
		}
		else 
		{
			i16_TmpKi_0 = m_i16_KiInvCurrRmsReg_0 * 2;
		}
		
		
		i16_TmpDx_0 = ((INT32)i16_TmpRMSRef_0 * 1536)>>10;		
		
		if((objOutput.m_i16_TpriIoutPrms <<2) >= i16_TmpDx_0
			&&objOutput.m_i16_TpriIoutPrms >= 154				
			&&(objOutput.m_i16_TsndIoutPrms <<2) <= i16_TmpRMSRef_0)
		{
			m_i16_IerrInvRms_0 = i16_TmpRMSRef_0 - (objOutput.m_i16_TpriIoutPrms<<2);
			UPDNLMT16(m_i16_IerrInvRms_0,310,-310);				
		}
		else
		{
			m_i16_IerrInvRms_0 = i16_TmpRMSRef_0 - (objOutput.m_i16_TsndIoutPrms<<2);
			UPDNLMT16(m_i16_IerrInvRms_0,310,-310);				
		}

		m_i16_IRmsCmp_0 = m_un_IntgInvIRRms_0.half.hword + (((INT32)m_i16_IerrInvRms_0 * i16_TmpKp_0)>>12);	
		UPDNLMT16(m_i16_IRmsCmp_0,4096,-4096);					

		m_un_IntgInvIRRms_0.dword += ((INT32)m_i16_IerrInvRms_0 * i16_TmpKi_0);
		UPDNLMT32(m_un_IntgInvIRRms_0.dword,0x10000000,-0x10000000);
		
		m_i16_IRmsCmp_0 = ((INT32)m_i16_IRmsCmp_0 * 5792)>>12;
	}
	else
	{
		m_un_IntgInvIRRms_0.dword = 0;
		m_i16_IRmsCmp_0 = 0;	
	}

}