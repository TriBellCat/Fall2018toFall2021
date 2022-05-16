using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void RadioButtonList3_SelectedIndexChanged(object sender, EventArgs e)
    {

    }

    protected void CheckBoxList1_SelectedIndexChanged(object sender, EventArgs e)
    {

    }

    protected void TextBox1_TextChanged(object sender, EventArgs e)
    {

    }

    protected void TextBox2_TextChanged(object sender, EventArgs e)
    {

    }

    protected void TextBox3_TextChanged(object sender, EventArgs e)
    {

    }

    protected void Button1_Click(object sender, EventArgs e)
    {
        double pizzaPrice = double.Parse(RadioButtonList3.SelectedValue.ToString());
        double maxtop = CheckBoxList1.Items.Count;
        double toppings = 0;
        for (int i = 0; i < maxtop; i++)
        {
            if (CheckBoxList1.Items[i].Selected)
                toppings += double.Parse(CheckBoxList1.Items[i].Value);
        }

        double subTotal = pizzaPrice + toppings;
        double tax = subTotal * .0875;
        double total = subTotal + tax;

        TextBox1.Text = subTotal.ToString("C");
        TextBox2.Text = tax.ToString("C");
        TextBox3.Text = total.ToString("C");
    }
}